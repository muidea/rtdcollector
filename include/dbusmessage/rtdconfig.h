#ifndef __RTDCONFIG_H_1333__
#define __RTDCONFIG_H_1333__
#include "rtd/rtdInfo.h"
#include <dbus/dbus.h>

namespace RtdDBus
{
    bool encodeRtdConfig(Rtd::ConfigInfo const& rtdConfig, DBusMessage* dbusMsg);
}

#endif // __RTDCONFIG_H_1333__
