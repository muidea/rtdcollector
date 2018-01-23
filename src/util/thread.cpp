//
// Thread.cpp
//
// Library: Foundation
// Package: Threading
// Module:  Thread
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "util/thread.h"
#include "util/mutex.h"
#include "util/exception.h"
#include "util/threadLocal.h"
#include "util/atomicCounter.h"
#include <sstream>


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "thread_WIN32.cpp"
#else
#include "thread_POSIX.cpp"
#endif

namespace Util {


namespace {

class RunnableHolder: public Runnable
{
public:
	RunnableHolder(Runnable& target):
		_target(target)
	{
	}

	~RunnableHolder()
	{
	}

	void run()
	{
		_target.run();
	}

private:
	Runnable& _target;
};


class CallableHolder: public Runnable
{
public:
	CallableHolder(Thread::Callable callable, void* pData):
		_callable(callable),
		_pData(pData)
	{
	}

	~CallableHolder()
	{
	}

	void run()
	{
		_callable(_pData);
	}

private:
	Thread::Callable _callable;
	void* _pData;
};


} // namespace


Thread::Thread(): 
	_id(uniqueId()), 
	_name(makeName()), 
	_pTLS(0),
	_event(true)
{
}


Thread::Thread(const std::string& name): 
	_id(uniqueId()), 
	_name(name), 
	_pTLS(0),
	_event(true)
{
}


Thread::~Thread()
{
	delete _pTLS;
}


void Thread::setPriority(Priority prio)
{
	setPriorityImpl(prio);
}


Thread::Priority Thread::getPriority() const
{
	return Priority(getPriorityImpl());
}


void Thread::start(Runnable& target)
{
	startImpl(new RunnableHolder(target));
}


void Thread::start(Callable target, void* pData)
{
	startImpl(new CallableHolder(target, pData));
}


void Thread::join()
{
	joinImpl();
}


void Thread::join(long milliseconds)
{
	if (!joinImpl(milliseconds))
		throw TimeoutException();
}


bool Thread::tryJoin(long milliseconds)
{
	return joinImpl(milliseconds);
}


bool Thread::trySleep(long milliseconds)
{
	Thread* pT = Thread::current();
	util_check_ptr(pT);
	return !(pT->_event.tryWait(milliseconds));
}


void Thread::wakeUp()
{
	_event.set();
}


ThreadLocalStorage& Thread::tls()
{
	if (!_pTLS)
		_pTLS = new ThreadLocalStorage;
	return *_pTLS;
}


void Thread::clearTLS()
{
	if (_pTLS)
	{
		delete _pTLS;
		_pTLS = 0;
	}
}


std::string Thread::makeName()
{
	std::ostringstream name;
	name << '#' << _id;
	return name.str();
}


int Thread::uniqueId()
{
	static Util::AtomicCounter counter;
	return ++counter;
}


void Thread::setName(const std::string& name)
{
	FastMutex::ScopedLock lock(_mutex);

	_name = name;
}


} // namespace Util
