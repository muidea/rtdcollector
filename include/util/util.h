//
// port from poco-1.8.1
//


#ifndef __FOUNDATION_H_1449__
#define __FOUNDATION_H_1449__

//
// Include library configuration
//
#include "config.h"

//
// Ensure that UTIL_DLL is default unless UTIL_STATIC is defined
//
#if defined(_WIN32) && defined(_DLL)
	#if !defined(UTIL_DLL) && !defined(UTIL_STATIC)
		#define UTIL_DLL
	#endif
#endif


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the Util_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// Util_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(UTIL_DLL)
	#if defined(Util_EXPORTS)
		#define Util_API __declspec(dllexport)
	#else
		#define Util_API __declspec(dllimport)
	#endif
#endif


#if !defined(Util_API)
	#if !defined(UTIL_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define Util_API __attribute__ ((visibility ("default")))
	#else
		#define Util_API
	#endif
#endif


//
// Automatically link Foundation library.
//
#if defined(_MSC_VER)
	#if defined(UTIL_DLL)
		#if defined(_DEBUG)
			#define UTIL_LIB_SUFFIX ".lib"
		#else
			#define UTIL_LIB_SUFFIX ".lib"
		#endif
	#elif defined(_DLL)
		#if defined(_DEBUG)
			#define UTIL_LIB_SUFFIX "md.lib"
		#else
			#define UTIL_LIB_SUFFIX "md.lib"
		#endif
	#else
		#if defined(_DEBUG)
			#define UTIL_LIB_SUFFIX "mt.lib"
		#else
			#define UTIL_LIB_SUFFIX "mt.lib"
		#endif
	#endif

	#if !defined(UTIL_NO_AUTOMATIC_LIBS) && !defined(Util_EXPORTS)
		#pragma comment(lib, "util" UTIL_LIB_SUFFIX)
	#endif
#endif


//
// Include platform-specific definitions
//
#include "../platform.h"
#if defined(_WIN32)
	#include "platform_WIN32.h"
#elif defined(PLATFORM_OS_FAMILY_UNIX)
	#include "platform_POSIX.h"
#endif


//
// Include alignment settings early
//
#include "alignment.h"

//
// Cleanup inconsistencies
//
#ifdef PLATFORM_OS_FAMILY_WINDOWS
	#if defined(UTIL_WIN32_UTF8) && defined(UTIL_NO_WSTRING)
		#error UTIL_WIN32_UTF8 and UTIL_NO_WSTRING are mutually exclusive.
	#endif
#else
	#ifdef UTIL_WIN32_UTF8
		#undef UTIL_WIN32_UTF8
	#endif
#endif


//
// UTIL_JOIN
//
// The following piece of macro magic joins the two
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expansion of macro arguments does not
// occur in UTIL_DO_JOIN2 but does in UTIL_DO_JOIN.
//
#define UTIL_JOIN(X, Y) UTIL_DO_JOIN(X, Y)
#define UTIL_DO_JOIN(X, Y) UTIL_DO_JOIN2(X, Y)
#define UTIL_DO_JOIN2(X, Y) X##Y


//
// UTIL_DEPRECATED
//
// A macro expanding to a compiler-specific clause to
// mark a class or function as deprecated.
//
#if defined(UTIL_NO_DEPRECATED)
#define UTIL_DEPRECATED
#elif defined(_GNUC_)
#define UTIL_DEPRECATED __attribute__((deprecated))
#elif defined(__clang__)
#define UTIL_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define UTIL_DEPRECATED __declspec(deprecated)
#else
#define UTIL_DEPRECATED
#endif


//
// Pull in basic definitions
//
#include "bugCheck.h"
#include "types.h"
#include <string>


#endif // __FOUNDATION_H_1449__
