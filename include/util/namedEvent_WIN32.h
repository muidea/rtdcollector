//
// NamedEvent_WIN32.h
//
// Library: Foundation
// Package: Processes
// Module:  NamedEvent
//
// Definition of the NamedEventImpl class for Windows.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef __NAMEEVENT_WIN32_H_1041__
#define __NAMEEVENT_WIN32_H_1041__


#include "util.h"
#include "unWindows.h"


namespace Util {


class Util_API NamedEventImpl
{
protected:
	NamedEventImpl(const std::string& name);	
	~NamedEventImpl();
	void setImpl();
	void waitImpl();
	
private:
	std::string _name;
	HANDLE      _event;	
};


} // namespace Util


#endif // __NAMEEVENT_WIN32_H_1041__
