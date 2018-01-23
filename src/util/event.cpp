//
// Event.cpp
//
// Library: Foundation
// Package: Threading
// Module:  Event
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "util/event.h"


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "event_WIN32.cpp"
#else
#include "event_POSIX.cpp"
#endif


namespace Util {


Event::Event(bool autoReset): EventImpl(autoReset)
{
}


Event::~Event()
{
}


} // namespace Poco
