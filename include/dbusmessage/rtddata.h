#ifndef __RTD_DATA_H_1403__
#define __RTD_DATA_H_1403__
#include "rtd/rtdInfo.h"
#include <dbus/dbus.h>

namespace RtdDBus
{
    bool encodeRtdData(Rtd::RtdDataVector const& rtdData, DBusMessage* dbusMsg);
    
    bool decodeRtdData(DBusMessage* dbusMsg, Rtd::RtdDataVector& rtdData);
}

#endif // __RTD_DATA_H_1403__