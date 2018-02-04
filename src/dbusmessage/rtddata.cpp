#include "dbusmessage/rtddata.h"

namespace RtdDBus
{
    bool encodeRtdData(Rtd::RtdDataVector const &rtdData, DBusMessage *dbusMsg)
    {
        DBusMessageIter dbusMsgIter;
        dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);
                
    }
}