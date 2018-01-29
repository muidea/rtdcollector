//
// port from poco-1.8.1
//


#include "util/pipeImpl.h"


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "pipeImpl_WIN32.cpp"
#elif defined(PLATFORM_OS_FAMILY_UNIX)
#include "pipeImpl_POSIX.cpp"
#endif
