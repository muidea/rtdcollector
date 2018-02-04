#ifndef __RTD_EVENT_H_1425__
#define __RTD_EVENT_H_1425__
#include "rtd/rtdInfo.h"
#include <dbus/dbus.h>

namespace RtdDBus
{
    bool encodeRtdEvent(Rtd::RtdEventVector const& rtdEvent, DBusMessage* dbusMsg);
}


#endif // __RTD_EVENT_H_1425__