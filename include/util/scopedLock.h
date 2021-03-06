//
// port from poco-1.8.1
//

#ifndef __SCOPELOCK_H_1405__
#define __SCOPELOCK_H_1405__


#include "util.h"


namespace Util {


template <class M>
class ScopedLock
	/// A class that simplifies thread synchronization
	/// with a mutex.
	/// The constructor accepts a Mutex (and optionally
	/// a timeout value in milliseconds) and locks it.
	/// The destructor unlocks the mutex.
{
public:
	explicit ScopedLock(M& mutex): _mutex(mutex)
	{
		_mutex.lock();
	}
	
	ScopedLock(M& mutex, long milliseconds): _mutex(mutex)
	{
		_mutex.lock(milliseconds);
	}
	
	~ScopedLock()
	{
		try
		{
			_mutex.unlock();
		}
		catch (...)
		{
			util_unexpected();
		}
	}

private:
	M& _mutex;

	ScopedLock();
	ScopedLock(const ScopedLock&);
	ScopedLock& operator = (const ScopedLock&);
};


template <class M>
class ScopedLockWithUnlock
	/// A class that simplifies thread synchronization
	/// with a mutex.
	/// The constructor accepts a Mutex (and optionally
	/// a timeout value in milliseconds) and locks it.
	/// The destructor unlocks the mutex.
	/// The unlock() member function allows for manual
	/// unlocking of the mutex.
{
public:
	explicit ScopedLockWithUnlock(M& mutex): _pMutex(&mutex)
	{
		_pMutex->lock();
	}
	
	ScopedLockWithUnlock(M& mutex, long milliseconds): _pMutex(&mutex)
	{
		_pMutex->lock(milliseconds);
	}
	
	~ScopedLockWithUnlock()
	{
		try
		{
			unlock();
		}
		catch (...)
		{
			util_unexpected();
		}
	}
	
	void unlock()
	{
		if (_pMutex)
		{
			_pMutex->unlock();
			_pMutex = 0;
		}
	}

private:
	M* _pMutex;

	ScopedLockWithUnlock();
	ScopedLockWithUnlock(const ScopedLockWithUnlock&);
	ScopedLockWithUnlock& operator = (const ScopedLockWithUnlock&);
};


} // namespace Util


#endif // __SCOPELOCK_H_1405__
