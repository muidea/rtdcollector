#ifndef __DEF_H_1650__
#define __DEF_H_1650__


#if defined(_WIN32) && defined(_DLL)
	#if !defined(DBUSWRAPPER_DLL) && !defined(DBUSWRAPPER_STATIC)
		#define DBUSWRAPPER_DLL
	#endif
#endif


#if defined(_WIN32) && defined(DBUSWRAPPER_DLL)
	#if defined(DBUSWRAPPER_EXPORTS)
		#define DBusWrapper_API __declspec(dllexport)
	#else
		#define DBusWrapper_API __declspec(dllimport)
	#endif
#endif

#if !defined(DBusWrapper_API)
	#if !defined(UTIL_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define DBusWrapper_API __attribute__ ((visibility ("default")))
	#else
		#define DBusWrapper_API
	#endif
#endif


#endif