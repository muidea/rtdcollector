//
// port from poco-1.8.1
//


#include "util/mutex.h"


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "mutex_WIN32.cpp"
#else
#include "mutex_POSIX.cpp"
#endif

namespace Util {


Mutex::Mutex()
{
}


Mutex::~Mutex()
{
}


FastMutex::FastMutex()
{
}


FastMutex::~FastMutex()
{
}


} // namespace Util
