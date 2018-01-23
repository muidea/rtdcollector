#ifndef __DEF_H_1107__
#define __DEF_H_1107__


#if defined(_WIN32) && defined(_DLL)
	#if !defined(RTDCOLLECTOR_DLL) && !defined(RTDCOLLECTOR_STATIC)
		#define RTDCOLLECTOR_DLL
	#endif
#endif


#if defined(_WIN32) && defined(RTDCOLLECTOR_DLL)
	#if defined(RTDCOLLECTOR_EXPORTS)
		#define RtdCollector_API __declspec(dllexport)
	#else
		#define RtdCollector_API __declspec(dllimport)
	#endif
#endif

#if !defined(RtdCollector_API)
	#if !defined(UTIL_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define RtdCollector_API __attribute__ ((visibility ("default")))
	#else
		#define RtdCollector_API
	#endif
#endif


#endif