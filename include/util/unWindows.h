//
// port from poco-1.8.1
//

#ifndef __UNWINDOWS_H_1511__
#define __UNWINDOWS_H_1511__


// Reduce bloat
#if defined(_WIN32)
	#if !defined(WIN32_LEAN_AND_MEAN) && !defined(UTIL_BLOATED_WIN32)
		#define WIN32_LEAN_AND_MEAN
	#endif
#endif


// Microsoft Visual C++ includes copies of the Windows header files 
// that were current at the time Visual C++ was released.
// The Windows header files use macros to indicate which versions 
// of Windows support many programming elements. Therefore, you must 
// define these macros to use new functionality introduced in each 
// major operating system release. (Individual header files may use 
// different macros; therefore, if compilation problems occur, check 
// the header file that contains the definition for conditional 
// definitions.) For more information, see SdkDdkVer.h.


#if defined(_WIN32_WINNT)
	#if (_WIN32_WINNT < 0x0501)
		#error Unsupported Windows version.
	#endif
#elif defined(NTDDI_VERSION)
	#if (NTDDI_VERSION < 0x05010100)
		#error Unsupported Windows version.
	#endif
#elif !defined(_WIN32_WINNT)
	// Define minimum supported version.
	// This can be changed, if needed.
	// If allowed (see UTIL_MIN_WINDOWS_OS_SUPPORT
	// below), Platform_WIN32.h will do its
	// best to determine the appropriate values
	// and may redefine these. See Platform_WIN32.h
	// for details.
	#define _WIN32_WINNT 0x0501
	#define NTDDI_VERSION 0x05010100
#endif


// To prevent Platform_WIN32.h to modify version defines,
// uncomment this, otherwise versions will be automatically
// discovered in Platform_WIN32.h.
// #define UTIL_FORCE_MIN_WINDOWS_OS_SUPPORT


#include <windows.h>

#endif // __UNWINDOWS_H_1511__
