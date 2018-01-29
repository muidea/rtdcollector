//
// NamedEvent.cpp
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


#include "util/namedEvent.h"


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "namedEvent_WIN32.cpp"
#elif defined(PLATFORM_OS_FAMILY_UNIX)
#include "namedEvent_POSIX.cpp"
#endif


namespace Util {


NamedEvent::NamedEvent(const std::string& name):
	NamedEventImpl(name)
{
}


NamedEvent::~NamedEvent()
{
}


} // namespace Util
