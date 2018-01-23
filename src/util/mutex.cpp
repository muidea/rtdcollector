//
// Mutex.cpp
//
// Library: Foundation
// Package: Threading
// Module:  Mutex
//
// Copyright (c) 2004-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "util/mutex.h"


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "mutex_WIN32.cpp"
#else
#include "mutex_POSIX.cpp"
#endif

namespace Util {


Mutex::Mutex()
{
}


Mutex::~Mutex()
{
}


FastMutex::FastMutex()
{
}


FastMutex::~FastMutex()
{
}


} // namespace Util
