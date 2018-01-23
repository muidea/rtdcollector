//
// Timestamp.cpp
//
// Library: Foundation
// Package: DateTime
// Module:  Timestamp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "util/timestamp.h"
#include "util/timespan.h"
#include "util/exception.h"
#include <algorithm>
#undef min
#undef max
#include <limits>
#if defined(PLATFORM_OS_FAMILY_UNIX)
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/times.h>
#elif defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "util/unWindows.h"
#endif

namespace Util {


const Timestamp::TimeVal Timestamp::TIMEVAL_MIN = std::numeric_limits<Timestamp::TimeVal>::min();
const Timestamp::TimeVal Timestamp::TIMEVAL_MAX = std::numeric_limits<Timestamp::TimeVal>::max();


Timestamp::Timestamp()
{
	update();
}


Timestamp::Timestamp(TimeVal tv)
{
	_ts = tv;
}


Timestamp::Timestamp(const Timestamp& other)
{
	_ts = other._ts;
}


Timestamp::~Timestamp()
{
}


Timestamp& Timestamp::operator = (const Timestamp& other)
{
	_ts = other._ts;
	return *this;
}


Timestamp& Timestamp::operator = (TimeVal tv)
{
	_ts = tv;
	return *this;
}


void Timestamp::swap(Timestamp& timestamp)
{
	std::swap(_ts, timestamp._ts);
}


Timestamp Timestamp::fromEpochTime(std::time_t t)
{
	return Timestamp(TimeVal(t)*resolution());
}


Timestamp Timestamp::fromUtcTime(UtcTimeVal val)
{
	val -= (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
	val /= 10;
	return Timestamp(val);
}


void Timestamp::update()
{
#if defined(PLATFORM_OS_FAMILY_WINDOWS)

	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	epoch.LowPart  = 0xD53E8000;
	epoch.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart  = ft.dwLowDateTime;
	ts.HighPart = ft.dwHighDateTime;
	ts.QuadPart -= epoch.QuadPart;
	_ts = ts.QuadPart/10;

#elif defined(PLATFORM_HAVE_CLOCK_GETTIME)

	struct timespec ts;
	if (clock_gettime(CLOCK_REALTIME, &ts))
		throw SystemException("cannot get time of day");
	_ts = TimeVal(ts.tv_sec)*resolution() + ts.tv_nsec/1000;

#else

	struct timeval tv;
	if (gettimeofday(&tv, NULL))
		throw SystemException("cannot get time of day");
	_ts = TimeVal(tv.tv_sec)*resolution() + tv.tv_usec;

#endif
}


Timestamp  Timestamp::operator +  (const Timespan& span) const
{
	return *this + span.totalMicroseconds();
}


Timestamp  Timestamp::operator -  (const Timespan& span) const
{
	return *this - span.totalMicroseconds();
}


Timestamp& Timestamp::operator += (const Timespan& span)
{
	return *this += span.totalMicroseconds();
}


Timestamp& Timestamp::operator -= (const Timespan& span)
{
	return *this -= span.totalMicroseconds();
}


#if defined(_WIN32)


Timestamp Timestamp::fromFileTimeNP(UInt32 fileTimeLow, UInt32 fileTimeHigh)
{
	ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	epoch.LowPart  = 0xD53E8000;
	epoch.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart  = fileTimeLow;
	ts.HighPart = fileTimeHigh;
	ts.QuadPart -= epoch.QuadPart;

	return Timestamp(ts.QuadPart/10);
}


void Timestamp::toFileTimeNP(UInt32& fileTimeLow, UInt32& fileTimeHigh) const
{
	ULARGE_INTEGER epoch; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	epoch.LowPart  = 0xD53E8000;
	epoch.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.QuadPart  = _ts*10;
	ts.QuadPart += epoch.QuadPart;
	fileTimeLow  = ts.LowPart;
	fileTimeHigh = ts.HighPart;
}


#endif


} // namespace Util
