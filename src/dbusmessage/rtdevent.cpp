#include "dbusmessage/rtdevent.h"

namespace RtdDBus
{
    bool encodeRtdEvent(Rtd::RtdEventVector const &rtdEvent, DBusMessage *dbusMsg)
    {
        DBusMessageIter dbusMsgIter;
        dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);

        DBusMessageIter structIter;
        for (auto iter = rtdEvent.begin(); iter != rtdEvent.end(); ++iter) {
            Rtd::RtdEvent const& val = *iter;

            dbus_message_iter_open_container(&dbusMsgIter, DBUS_TYPE_STRUCT, 0, &structIter);

            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.ownerID);
            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.timeStamp);
            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.eventID);

            dbus_message_iter_close_container(&dbusMsgIter, &structIter);
        }

        return true;
    }

    bool decodeRtdEvent(DBusMessage* dbusMsg, Rtd::RtdEventVector& rtdEvent)
    {
        DBusMessageIter dbusMsgIter;
        DBusBasicValue value;
        dbus_message_iter_init(dbusMsg,&dbusMsgIter);

        //rtdEvent.reserve(totalSize);

        DBusMessageIter structIter;

        while(dbus_message_iter_get_arg_type(&dbusMsgIter) == DBUS_TYPE_STRUCT) {
            Rtd::RtdEvent rtd;
            dbus_message_iter_recurse(&dbusMsgIter, &structIter);
            if(dbus_message_iter_get_arg_type(&structIter) == DBUS_TYPE_UINT64) {
                dbus_message_iter_get_basic(&structIter, &value);
                rtd.ownerID = value.u64;
            }

            dbus_message_iter_next(&structIter);
            if(dbus_message_iter_get_arg_type(&structIter) == DBUS_TYPE_UINT64) {
                dbus_message_iter_get_basic(&structIter, &value);
                rtd.timeStamp = value.u64;
            }

            dbus_message_iter_next(&structIter);
            if(dbus_message_iter_get_arg_type(&structIter) == DBUS_TYPE_UINT64) {
                dbus_message_iter_get_basic(&structIter, &value);
                rtd.eventID = value.u64;
            }

            rtdEvent.push_back(rtd);

            dbus_message_iter_next(&dbusMsgIter);
        }
        
        return true;
    }    
}