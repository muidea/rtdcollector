//
// port from poco-1.8.1
//

#ifndef __PLATFORM_POSIX_H_1509__
#define __PLATFORM_POSIX_H_1509__


//
// Thread-safety of local static initialization
//
#if __cplusplus >= 201103L || __GNUC__ >= 4 || defined(__clang__)
	#ifndef UTIL_LOCAL_STATIC_INIT_IS_THREADSAFE
		#define UTIL_LOCAL_STATIC_INIT_IS_THREADSAFE 1
	#endif
#endif


#endif // __PLATFORM_POSIX_H_1509__
