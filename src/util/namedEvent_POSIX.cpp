//
// NamedEvent_UNIX.cpp
//
// Library: Foundation
// Package: Processes
// Module:  NamedEvent
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "util/namedEvent_POSIX.h"
#include "util/exception.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


namespace Util {

	union semun
	{
		int                 val;
		struct semid_ds*    buf;
		unsigned short int* array;
		struct seminfo*     __buf;
	};


NamedEventImpl::NamedEventImpl(const std::string& name):
	_name(name)
{
	std::string fileName = getFileName();

	int fd = open(fileName.c_str(), O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd != -1)
		close(fd);
	else
		throw SystemException("cannot create named event", _name);
	key_t key = ftok(fileName.c_str(), 'p');
	if (key == -1)
		throw SystemException("cannot create named mutex", _name);
	_semid = semget(key, 1, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | IPC_CREAT | IPC_EXCL);
	if (_semid >= 0)
	{
		union semun arg;
		arg.val = 0;
		semctl(_semid, 0, SETVAL, arg);
	}
	else if (errno == EEXIST)
	{
		_semid = semget(key, 1, 0);
	}
	else throw SystemException("cannot create named mutex", _name);
}


NamedEventImpl::~NamedEventImpl()
{
}


void NamedEventImpl::setImpl()
{
	struct sembuf op;
	op.sem_num = 0;
	op.sem_op  = 1;
	op.sem_flg = 0;
	if (semop(_semid, &op, 1) != 0)
	   	throw SystemException("cannot set named event", _name);
}


void NamedEventImpl::waitImpl()
{
	struct sembuf op;
	op.sem_num = 0;
	op.sem_op  = -1;
	op.sem_flg = 0;
	int err;
	do
	{
		err = semop(_semid, &op, 1);
	}
	while (err && errno == EINTR);
	if (err) throw SystemException("cannot wait for named event", _name);
}


std::string NamedEventImpl::getFileName()
{
	std::string fn = "/tmp/";
	fn.append(_name);
	fn.append(".event");
	return fn;
}


} // namespace Util
