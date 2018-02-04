#include "dbusmessage/rtdevent.h"

namespace RtdDBus
{
    bool encodeRtdEvent(Rtd::RtdEventVector const &rtdEvent, DBusMessage *dbusMsg)
    {
        DBusMessageIter dbusMsgIter;
        dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);

    }
}