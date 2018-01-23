//
// AtomicCounter.h
//
// Library: Foundation
// Package: Core
// Module:  AtomicCounter
//
// Definition of the AtomicCounter class.
//
// Copyright (c) 2009, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef __ATOMICCOUNTER_H_1353__
#define __ATOMICCOUNTER_H_1353__


#include "util.h"
#if PLATFORM_OS == PLATFORM_OS_WINDOWS_NT
	#include "unWindows.h"
#elif ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2) || __GNUC__ > 4) && (defined(__x86_64__) || defined(__i386__))
	#if !defined(PLATFORM_HAVE_GCC_ATOMICS) && !defined(PLATFORM_NO_GCC_ATOMICS)
		#define PLATFORM_HAVE_GCC_ATOMICS
	#endif
#elif ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) || __GNUC__ > 4)
	#if !defined(PLATFORM_HAVE_GCC_ATOMICS) && !defined(PLATFORM_NO_GCC_ATOMICS)
		#define PLATFORM_HAVE_GCC_ATOMICS
	#endif
#endif // PLATFORM_OS
#include "mutex.h"
#ifdef PLATFORM_HAVE_STD_ATOMICS
#include <atomic>
#endif


namespace Util {


class Util_API AtomicCounter
	/// This class implements a simple counter, which
	/// provides atomic operations that are safe to
	/// use in a multithreaded environment.
	///
	/// Typical usage of AtomicCounter is for implementing
	/// reference counting and similar things.
	///
	/// On some platforms, the implementation of AtomicCounter
	/// is based on atomic primitives specific to the platform
	/// (such as InterlockedIncrement, etc. on Windows), and
	/// thus very efficient. On platforms that do not support
	/// atomic primitives, operations are guarded by a FastMutex.
	///
	/// The following platforms currently have atomic
	/// primitives:
	///   - Windows
	///   - Mac OS X
	///   - GCC 4.1+ (Intel platforms only)
{
public:
	typedef int ValueType; /// The underlying integer type.
	
	AtomicCounter();
		/// Creates a new AtomicCounter and initializes it to zero.
		
	explicit AtomicCounter(ValueType initialValue);
		/// Creates a new AtomicCounter and initializes it with
		/// the given value.
	
	AtomicCounter(const AtomicCounter& counter);
		/// Creates the counter by copying another one.
	
	~AtomicCounter();
		/// Destroys the AtomicCounter.

	AtomicCounter& operator = (const AtomicCounter& counter);
		/// Assigns the value of another AtomicCounter.
		
	AtomicCounter& operator = (ValueType value);
		/// Assigns a value to the counter.

	operator ValueType () const;
		/// Returns the value of the counter.
		
	ValueType value() const;
		/// Returns the value of the counter.
		
	ValueType operator ++ (); // prefix
		/// Increments the counter and returns the result.
		
	ValueType operator ++ (int); // postfix
		/// Increments the counter and returns the previous value.
		
	ValueType operator -- (); // prefix
		/// Decrements the counter and returns the result.
		
	ValueType operator -- (int); // postfix
		/// Decrements the counter and returns the previous value.
		
	bool operator ! () const;
		/// Returns true if the counter is zero, false otherwise.

private:
#if defined(PLATFORM_HAVE_STD_ATOMICS)
	typedef std::atomic<int> ImplType;
#elif PLATFORM_OS == PLATFORM_OS_WINDOWS_NT
	typedef volatile LONG ImplType;
#elif defined(PLATFORM_HAVE_GCC_ATOMICS)
	typedef int ImplType;
#else // generic implementation based on FastMutex
	struct ImplType
	{
		mutable FastMutex mutex;
		volatile int      value;
	};
#endif //

	ImplType _counter;
};


//
// inlines
//


#if defined(PLATFORM_HAVE_STD_ATOMICS)
//
// C++11 atomics
//
inline AtomicCounter::operator AtomicCounter::ValueType () const
{
	return _counter.load();
}

	
inline AtomicCounter::ValueType AtomicCounter::value() const
{
	return _counter.load();
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
	return ++_counter;
}

	
inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
	return _counter++;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
	return --_counter;
}

	
inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
	return _counter--;
}

	
inline bool AtomicCounter::operator ! () const
{
	return _counter.load() == 0;
}


#elif PLATFORM_OS == PLATFORM_OS_WINDOWS_NT
//
// Windows
//
inline AtomicCounter::operator AtomicCounter::ValueType () const
{
	return _counter;
}

	
inline AtomicCounter::ValueType AtomicCounter::value() const
{
	return _counter;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
	return InterlockedIncrement(&_counter);
}

	
inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
	ValueType result = InterlockedIncrement(&_counter);
	return --result;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
	return InterlockedDecrement(&_counter);
}

	
inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
	ValueType result = InterlockedDecrement(&_counter);
	return ++result;
}

	
inline bool AtomicCounter::operator ! () const
{
	return _counter == 0;
}

#elif defined(PLATFORM_HAVE_GCC_ATOMICS)
//
// GCC 4.1+ atomic builtins.
//
inline AtomicCounter::operator AtomicCounter::ValueType () const
{
	return _counter;
}

	
inline AtomicCounter::ValueType AtomicCounter::value() const
{
	return _counter;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
	return __sync_add_and_fetch(&_counter, 1);
}

	
inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
	return __sync_fetch_and_add(&_counter, 1);
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
	return __sync_sub_and_fetch(&_counter, 1);
}

	
inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
	return __sync_fetch_and_sub(&_counter, 1);
}

	
inline bool AtomicCounter::operator ! () const
{
	return _counter == 0;
}


#else
//
// Generic implementation based on FastMutex
//
inline AtomicCounter::operator AtomicCounter::ValueType () const
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value;
	}
	return result;
}

	
inline AtomicCounter::ValueType AtomicCounter::value() const
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value;
	}
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator ++ () // prefix
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = ++_counter.value;
	}
	return result;
}

	
inline AtomicCounter::ValueType AtomicCounter::operator ++ (int) // postfix
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value++;
	}
	return result;
}


inline AtomicCounter::ValueType AtomicCounter::operator -- () // prefix
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = --_counter.value;
	}
	return result;
}

	
inline AtomicCounter::ValueType AtomicCounter::operator -- (int) // postfix
{
	ValueType result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value--;
	}
	return result;
}

	
inline bool AtomicCounter::operator ! () const
{
	bool result;
	{
		FastMutex::ScopedLock lock(_counter.mutex);
		result = _counter.value == 0;
	}
	return result;
}


#endif


} // namespace Util


#endif // __ATOMICCOUNTER_H_1353__
