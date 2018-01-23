//
// Event_POSIX.h
//
// Library: Foundation
// Package: Threading
// Module:  Event
//
// Definition of the EventImpl class for POSIX Threads.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef __EVENT_POSIX_H_1340__
#define __EVENT_POSIX_H_1340__


#include "util.h"
#include "exception.h"
#include <pthread.h>
#include <errno.h>


namespace Util {


class Util_API EventImpl
{
protected:
	EventImpl(bool autoReset);		
	~EventImpl();
	void setImpl();
	void waitImpl();
	bool waitImpl(long milliseconds);
	void resetImpl();
	
private:
	bool            _auto;
	volatile bool   _state;
	pthread_mutex_t _mutex;
	pthread_cond_t  _cond;
};


//
// inlines
//
inline void EventImpl::setImpl()
{
	if (pthread_mutex_lock(&_mutex))	
		throw SystemException("cannot signal event (lock)");
	_state = true;
	if (pthread_cond_broadcast(&_cond))
	{
		pthread_mutex_unlock(&_mutex);
		throw SystemException("cannot signal event");
	}
	pthread_mutex_unlock(&_mutex);
}


inline void EventImpl::resetImpl()
{
	if (pthread_mutex_lock(&_mutex))	
		throw SystemException("cannot reset event");
	_state = false;
	pthread_mutex_unlock(&_mutex);
}


} // namespace Util


#endif // __EVENT_POSIX_H_1340__
