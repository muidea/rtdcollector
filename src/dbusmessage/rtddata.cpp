#include "dbusmessage/rtddata.h"

namespace RtdDBus
{
    bool encodeRtdData(Rtd::RtdDataVector const &rtdData, DBusMessage *dbusMsg)
    {
        DBusMessageIter dbusMsgIter;
        dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);

        DBusMessageIter vectorIter;
        DBusMessageIter structIter;
        DBusMessageIter valIter;
        
        const Util::UInt32 totalSize = rtdData.size();
        dbus_message_iter_append_basic(&dbusMsgIter, DBUS_TYPE_UINT32, &totalSize);

        dbus_message_iter_open_container(&dbusMsgIter, DBUS_TYPE_ARRAY, "(rtdData)",&vectorIter);
        for (auto iter = rtdData.begin(); iter != rtdData.end(); ++iter) {
            Rtd::RtdData const& val = *iter;

            dbus_message_iter_open_container(&vectorIter, DBUS_TYPE_STRUCT, 0, &structIter);

            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.ownerID);
            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.timeStamp);
            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.quality);

            dbus_message_iter_open_container(&structIter, DBUS_TYPE_STRUCT, 0, &valIter);
            dbus_message_iter_append_basic(&valIter,DBUS_TYPE_BYTE,&val.value.vt);
            dbus_message_iter_append_basic(&valIter,DBUS_TYPE_DOUBLE,&val.value.dblVal);
            dbus_message_iter_close_container(&structIter, &valIter);

            dbus_message_iter_close_container(&vectorIter, &structIter);
        }
        dbus_message_iter_close_container(&dbusMsgIter, &vectorIter);

        return true;
    }

    bool decodeRtdData(DBusMessage* dbusMsg, Rtd::RtdDataVector& rtdData)
    {
        DBusMessageIter dbusMsgIter;
        DBusBasicValue value;
        dbus_message_iter_init(dbusMsg,&dbusMsgIter);

        if (dbus_message_iter_get_arg_type(&dbusMsgIter)!= DBUS_TYPE_UINT32) {
            return false;
        }

        dbus_message_iter_get_basic(&dbusMsgIter, &value);
        Util::UInt32 totalSize = value.u32;

        rtdData.reserve(totalSize);

        DBusMessageIter vectorIter;
        DBusMessageIter structIter;
        DBusMessageIter valIter;

        dbus_message_iter_next(&dbusMsgIter);
        dbus_message_iter_recurse(&dbusMsgIter, &vectorIter);
        for (Util::UInt32 ii = 0; ii < totalSize; ++ii) {
            if(dbus_message_iter_get_arg_type(&vectorIter) == DBUS_TYPE_STRUCT) {
                Rtd::RtdData rtd;
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
                    rtd.quality = value.u64;
                }

                dbus_message_iter_next(&structIter);
                dbus_message_iter_recurse(&structIter, &valIter);
                if(dbus_message_iter_get_arg_type(&valIter) == DBUS_TYPE_BYTE) {
                    dbus_message_iter_get_basic(&valIter, &value);
                    rtd.value.vt = value.byt;
                }

                dbus_message_iter_next(&valIter);
                if(dbus_message_iter_get_arg_type(&valIter) == DBUS_TYPE_DOUBLE) {
                    dbus_message_iter_get_basic(&valIter, &value);
                    rtd.value.dblVal = value.dbl;
                }

                rtdData.push_back(rtd);
            }
            dbus_message_iter_next(&vectorIter);
        }

        return true;
    }
}