//
// NamedEvent_WIN32.cpp
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


#include "util/NamedEvent_WIN32.h"
#include "util/exception.h"


namespace Util {


NamedEventImpl::NamedEventImpl(const std::string& name):
	_name(name)
{
	_event = CreateEventA(NULL, FALSE, FALSE, _name.c_str());
	if (!_event)
	{
		DWORD dwRetVal = GetLastError();
		throw SystemException("cannot create named event", _name, (int)dwRetVal);
	}
}


NamedEventImpl::~NamedEventImpl()
{
	CloseHandle(_event);
}


void NamedEventImpl::setImpl()
{
	if (!SetEvent(_event))
		throw SystemException("cannot signal named event", _name);
}


void NamedEventImpl::waitImpl()
{
	switch (WaitForSingleObject(_event, INFINITE))
	{
	case WAIT_OBJECT_0:
		return;
	default:
		throw SystemException("wait for named event failed", _name);
	}
}


} // namespace Util
