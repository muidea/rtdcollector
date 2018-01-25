//
// port from poco-1.8.1
//

#ifndef __STREAMUTIL_H_1504__
#define __STREAMUTIL_H_1504__


#include "util.h"


// util_ios_init
//
// This is a workaround for a bug in the Dinkumware
// implementation of iostreams.
//
// Calling basic_ios::init() multiple times for the
// same basic_ios instance results in a memory leak
// caused by the ios' locale being allocated more than
// once, each time overwriting the old pointer.
// This usually occurs in the following scenario:
//
// class MyStreamBuf: public std::streambuf
// {
//     ...
// };
//
// class MyIOS: public virtual std::ios
// {
// public:
//     MyIOS()
//     {
//         init(&_buf);
//     }
// protected:
//     MyStreamBuf _buf;
// };
//
// class MyIStream: public MyIOS, public std::istream
// {
//     ...
// };
//
// In this scenario, std::ios::init() is called twice
// (the first time by the MyIOS constructor, the second
// time by the std::istream constructor), resulting in 
// two locale objects being allocated, the pointer second 
// one overwriting the pointer to the first one and thus 
// causing a memory leak.
// 
// The workaround is to call init() only once for each
// stream object - by the istream, ostream or iostream
// constructor, and not calling init() in ios-derived
// base classes.
//
// Some stream implementations, however, require that
// init() is called in the MyIOS constructor.
// Therefore we replace each call to init() with
// the util_ios_init macro defined below.


#if !defined(PLATFORM_IOS_INIT_HACK)
	// Microsoft Visual Studio with Dinkumware STL (but not STLport)
#	if defined(_MSC_VER) && (!defined(_STLP_MSVC) || defined(_STLP_NO_OWN_IOSTREAMS))
#		define PLATFORM_IOS_INIT_HACK 1
#	endif
#endif


#if defined(PLATFORM_IOS_INIT_HACK)
#	define util_ios_init(buf)
#else
#	define util_ios_init(buf) init(buf)
#endif


#endif // __STREAMUTIL_H_1504__
