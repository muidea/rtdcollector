#include "dbusmessage/rtdevent.h"

namespace RtdDBus
{
    bool encodeRtdEvent(Rtd::RtdEventVector const &rtdEvent, DBusMessage *dbusMsg)
    {
        DBusMessageIter dbusMsgIter;
        dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);

        DBusMessageIter vectorIter;
        DBusMessageIter structIter;
        const Util::UInt32 totalSize = rtdEvent.size();
        dbus_message_iter_append_basic(&dbusMsgIter, DBUS_TYPE_UINT32, &totalSize);
        
        dbus_message_iter_open_container(&dbusMsgIter, DBUS_TYPE_ARRAY, "(rtdEvent)",&vectorIter);
        for (auto iter = rtdEvent.begin(); iter != rtdEvent.end(); ++iter) {
            Rtd::RtdEvent const& val = *iter;

            dbus_message_iter_open_container(&vectorIter, DBUS_TYPE_STRUCT, 0, &structIter);

            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.ownerID);
            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.timeStamp);
            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.eventID);

            dbus_message_iter_close_container(&vectorIter, &structIter);
        }
        dbus_message_iter_close_container(&dbusMsgIter, &vectorIter);

        return true;
    }

    bool decodeRtdEvent(DBusMessage* dbusMsg, Rtd::RtdEventVector& rtdEvent)
    {
        DBusMessageIter dbusMsgIter;
        DBusBasicValue value;
        dbus_message_iter_init(dbusMsg,&dbusMsgIter);

        if (dbus_message_iter_get_arg_type(&dbusMsgIter)!= DBUS_TYPE_UINT32) {
            return false;
        }

        dbus_message_iter_get_basic(&dbusMsgIter, &value);
        Util::UInt32 totalSize = value.u32;

        rtdEvent.reserve(totalSize);

        DBusMessageIter vectorIter;
        DBusMessageIter structIter;

        dbus_message_iter_next(&dbusMsgIter);
        dbus_message_iter_recurse(&dbusMsgIter, &vectorIter);
        for (Util::UInt32 ii = 0; ii < totalSize; ++ii) {
            if(dbus_message_iter_get_arg_type(&vectorIter) == DBUS_TYPE_STRUCT) {
                Rtd::RtdEvent rtd;
                dbus_message_iter_recurse(&vectorIter, &structIter);
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
            }
            dbus_message_iter_next(&vectorIter);
        }
        
        return true;
    }    
}