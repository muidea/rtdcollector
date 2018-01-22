//
// port from poco-1.8.1
//


#ifndef __TYPES_H_1447__
#define __TYPES_H_1447__


#include "util.h"


namespace Util {


#if defined(_MSC_VER)
	//
	// Windows/Visual C++
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	typedef signed __int64         Int64;
	typedef unsigned __int64       UInt64;
	#if defined(_WIN64)
		#define PLATFORM_PTR_IS_64_BIT 1
		typedef signed __int64     IntPtr;
		typedef unsigned __int64   UIntPtr;
	#else
		typedef signed long        IntPtr;
		typedef unsigned long      UIntPtr;
	#endif
	#define PLATFORM_HAVE_INT64 1
#elif defined(__GNUC__) || defined(__clang__)
	//
	// Unix/GCC/Clang
	//
	typedef signed char            Int8;
	typedef unsigned char          UInt8;
	typedef signed short           Int16;
	typedef unsigned short         UInt16;
	typedef signed int             Int32;
	typedef unsigned int           UInt32;
	#if defined(_WIN64)
		#define PLATFORM_PTR_IS_64_BIT 1
		typedef signed long long   IntPtr;
		typedef unsigned long long UIntPtr;
		typedef signed long long   Int64;
		typedef unsigned long long UInt64;
	#else
		typedef signed long        IntPtr;
		typedef unsigned long      UIntPtr;
		#if defined(__LP64__)
			#define PLATFORM_PTR_IS_64_BIT 1
			#define PLATFORM_LONG_IS_64_BIT 1
			typedef signed long        Int64;
			typedef unsigned long      UInt64;
		#else
			typedef signed long long   Int64;
			typedef unsigned long long UInt64;
		#endif
	#endif
	#define PLATFORM_HAVE_INT64 1
#endif


} // namespace Util


#endif // __TYPES_H_1447__
