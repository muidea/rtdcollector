//
// port from poco-1.8.1
//

#include "util/event.h"


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
#include "event_WIN32.cpp"
#else
#include "event_POSIX.cpp"
#endif


namespace Util {


Event::Event(bool autoReset): EventImpl(autoReset)
{
}


Event::~Event()
{
}


} // namespace Poco
