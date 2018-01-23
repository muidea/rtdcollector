//
// FPEnvironment.cpp
//
// Library: Foundation
// Package: Core
// Module:  FPEnvironment
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


// pull in platform identification macros needed below
#include "platform.h"
#include "util/fPEnvironment.h"


#if defined(PLATFORM_OS_FAMILY_UNIX)
#include "fPEnvironment_C99.cpp"
#else
#include "fPEnvironment_WIN32.cpp"
#endif


namespace Util {


FPEnvironment::FPEnvironment()
{
}


FPEnvironment::FPEnvironment(RoundingMode rm)
{
	setRoundingMode(rm);
}


FPEnvironment::FPEnvironment(const FPEnvironment& env): FPEnvironmentImpl(env)
{
}


FPEnvironment::~FPEnvironment()
{
}


FPEnvironment& FPEnvironment::operator = (const FPEnvironment& env)
{
	if (&env != this)
	{
		FPEnvironmentImpl::operator = (env);
	}
	return *this;
}


void FPEnvironment::keepCurrent()
{
	keepCurrentImpl();
}


void FPEnvironment::clearFlags()
{
	clearFlagsImpl();
}


} // namespace Util
