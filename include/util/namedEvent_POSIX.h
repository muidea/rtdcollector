//
// NamedEvent_UNIX.h
//
// Library: Foundation
// Package: Processes
// Module:  NamedEvent
//
// Definition of the NamedEventImpl class for Unix.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef __NAMEEVENT_POSIX_H_039__
#define __NAMEEVENT_POSIX_H_039__


#include "util.h"


namespace Util {


class Util_API NamedEventImpl
{
protected:
	NamedEventImpl(const std::string& name);	
	~NamedEventImpl();
	void setImpl();
	void waitImpl();
	
private:
	std::string getFileName();

	std::string _name;
	int _semid;  // semaphore id
};


} // namespace Util


#endif // __NAMEEVENT_POSIX_H_039__
