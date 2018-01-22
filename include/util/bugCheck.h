//
// port from poco-1.8.1
//


#ifndef __BUGCHECK_H_1456__
#define __BUGCHECK_H_1456__


#include "util.h"
#include <string>
#include <cstdlib>
#if defined(_DEBUG)
#	include <iostream>
#endif


namespace Util {


class Util_API Bugcheck
	/// This class provides some static methods that are
	/// used by the
	/// util_assert_dbg(), util_assert(), util_check_ptr(), 
	/// util_bugcheck() and util_unexpected() macros. 
	/// You should not invoke these methods
	/// directly. Use the macros instead, as they
	/// automatically provide useful context information.
{
public:
	static void assertion(const char* cond, const char* file, int line, const char* text = 0);
		/// An assertion failed. Break into the debugger, if
		/// possible, then throw an AssertionViolationException.

	static void nullPointer(const char* ptr, const char* file, int line);
		/// An null pointer was encountered. Break into the debugger, if
		/// possible, then throw an NullPointerException.

	static void bugcheck(const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible, then throw an BugcheckException.

	static void bugcheck(const char* msg, const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible, then throw an BugcheckException.

	static void unexpected(const char* file, int line);
		/// An exception was caught in a destructor. Break into debugger,
		/// if possible and report exception. Must only be called from
		/// within a catch () block as it rethrows the exception to
		/// determine its class.

	static void debugger(const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible.

	static void debugger(const char* msg, const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible.

protected:
	static std::string what(const char* msg, const char* file, int line, const char* text = 0);
};


} // namespace Util


//
// useful macros (these automatically supply line number and file name)
//
#if defined(__KLOCWORK__) || defined(__clang_analyzer__)


// Short-circuit these macros when under static analysis.
// Ideally, static analysis tools should understand and reason correctly about
// noreturn methods such as Bugcheck::bugcheck(). In practice, they don't.
// Help them by turning these macros into std::abort() as described here:
// https://developer.klocwork.com/documentation/en/insight/10-1/tuning-cc-analysis#Usingthe__KLOCWORK__macro

#include <cstdlib> // for abort
#define util_assert_dbg(cond)           do { if (!(cond)) std::abort(); } while (0)
#define util_assert_msg_dbg(cond, text) do { if (!(cond)) std::abort(); } while (0)
#define util_assert(cond)               do { if (!(cond)) std::abort(); } while (0)
#define util_assert_msg(cond, text)     do { if (!(cond)) std::abort(); } while (0)
#define util_check_ptr(ptr)             do { if (!(ptr)) std::abort(); } while (0)
#define util_bugcheck()                 do { std::abort(); } while (0)
#define util_bugcheck_msg(msg)          do { std::abort(); } while (0)


#else // defined(__KLOCWORK__) || defined(__clang_analyzer__)


#if defined(_DEBUG)
	#define util_assert_dbg(cond) \
		if (!(cond)) Util::Bugcheck::assertion(#cond, __FILE__, __LINE__); else (void) 0

	#define util_assert_msg_dbg(cond, text) \
		if (!(cond)) Util::Bugcheck::assertion(#cond, __FILE__, __LINE__, text); else (void) 0
#else
	#define util_assert_msg_dbg(cond, text)
	#define util_assert_dbg(cond)
#endif


#define util_assert(cond) \
	if (!(cond)) Util::Bugcheck::assertion(#cond, __FILE__, __LINE__); else (void) 0


#define util_assert_msg(cond, text) \
	if (!(cond)) Util::Bugcheck::assertion(#cond, __FILE__, __LINE__, text); else (void) 0


#define util_check_ptr(ptr) \
	if (!(ptr)) Util::Bugcheck::nullPointer(#ptr, __FILE__, __LINE__); else (void) 0


#define util_bugcheck() \
	Util::Bugcheck::bugcheck(__FILE__, __LINE__)


#define util_bugcheck_msg(msg) \
	Util::Bugcheck::bugcheck(msg, __FILE__, __LINE__)


#endif // defined(__KLOCWORK__) || defined(__clang_analyzer__)


#define util_unexpected() \
	Util::Bugcheck::unexpected(__FILE__, __LINE__);


#define util_debugger() \
	Util::Bugcheck::debugger(__FILE__, __LINE__)


#define util_debugger_msg(msg) \
	Util::Bugcheck::debugger(msg, __FILE__, __LINE__)


#if defined(_DEBUG)
#	define util_stdout_dbg(outstr) \
	std::cout << __FILE__ << '(' << std::dec << __LINE__ << "):" << outstr << std::endl;
#else
#	define util_stdout_dbg(outstr)
#endif


#if defined(_DEBUG)
#	define util_stderr_dbg(outstr) \
		std::cerr << __FILE__ << '(' << std::dec << __LINE__ << "):" << outstr << std::endl;
#else
#	define util_stderr_dbg(outstr)
#endif


//
// util_static_assert
//
// The following was ported from <boost/static_assert.hpp>
//


template <bool x>
struct UTIL_STATIC_ASSERTION_FAILURE;


template <>
struct UTIL_STATIC_ASSERTION_FAILURE<true>
{
	enum
	{
		value = 1
	};
};


template <int x> 
struct util_static_assert_test
{
};


#if defined(__GNUC__) && (__GNUC__ == 3) && ((__GNUC_MINOR__ == 3) || (__GNUC_MINOR__ == 4))
#define util_static_assert(B) \
	typedef char UTIL_JOIN(util_static_assert_typedef_, __LINE__) \
        [UTIL_STATIC_ASSERTION_FAILURE<(bool) (B)>::value]
#else
#define util_static_assert(B) \
	typedef util_static_assert_test<sizeof(UTIL_STATIC_ASSERTION_FAILURE<(bool) (B)>)> \
		UTIL_JOIN(util_static_assert_typedef_, __LINE__) UTIL_UNUSED
#endif


#endif // __BUGCHECK_H_1456__
