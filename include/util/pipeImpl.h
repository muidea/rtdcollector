//
// port from poco-1.8.1
//


#ifndef __PIPEIMPL_H_1355__
#define __PIPEIMPL_H_1355__


#include "util.h"


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "pipeImpl_WIN32.h"
#elif defined(PLATFORM_OS_FAMILY_UNIX)
#include "pipeImpl_POSIX.h"
#endif


#endif // __PIPEIMPL_H_1355__
