#include "dbusmessage/rtddata.h"
#include <iostream>

namespace RtdDBus
{
    bool encodeRtdData(Rtd::RtdDataVector const &rtdData, DBusMessage *dbusMsg)
    {
        DBusMessageIter dbusMsgIter;
        dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);

        DBusMessageIter structIter;        
        for (auto iter = rtdData.begin(); iter != rtdData.end(); ++iter) {
            Rtd::RtdData const& val = *iter;

            dbus_message_iter_open_container(&dbusMsgIter, DBUS_TYPE_STRUCT, 0, &structIter);

            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.ownerID);
            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.timeStamp);
            dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.quality);

			switch (val.value.vt)
			{
			case Rtd::ValueType_Bool:
                dbus_message_iter_append_basic(&structIter,DBUS_TYPE_BOOLEAN,&val.value.boolVal);
				break;
			case Rtd::ValueType_I1:
                dbus_message_iter_append_basic(&structIter,DBUS_TYPE_INT16,&val.value.i1Val);
				break;
			case Rtd::ValueType_I2:
                dbus_message_iter_append_basic(&structIter,DBUS_TYPE_INT16,&val.value.i2Val);
				break;
			case Rtd::ValueType_I4:
				dbus_message_iter_append_basic(&structIter,DBUS_TYPE_INT32,&val.value.i4Val);
				break;
			case Rtd::ValueType_I8:
				dbus_message_iter_append_basic(&structIter,DBUS_TYPE_INT64,&val.value.i8Val);
				break;
			case Rtd::ValueType_UI1:
                dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT16,&val.value.ui1Val);
				break;
			case Rtd::ValueType_UI2:
				dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT16,&val.value.ui2Val);
				break;
			case Rtd::ValueType_UI4:
                dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT32,&val.value.ui4Val);
                break;
			case Rtd::ValueType_UI8:
                dbus_message_iter_append_basic(&structIter,DBUS_TYPE_UINT64,&val.value.ui8Val);
				break;
			case Rtd::ValueType_Float:
                dbus_message_iter_append_basic(&structIter,DBUS_TYPE_DOUBLE,&val.value.fltVal);
				break;
			case Rtd::ValueType_Double:
                dbus_message_iter_append_basic(&structIter,DBUS_TYPE_DOUBLE,&val.value.dblVal);
			default:
				break;
			}

            dbus_message_iter_close_container(&dbusMsgIter, &structIter);
        }

        return true;
    }

    bool decodeRtdData(DBusMessage* dbusMsg, Rtd::RtdDataVector& rtdData)
    {
        DBusMessageIter dbusMsgIter;
        DBusBasicValue value;
        dbus_message_iter_init(dbusMsg,&dbusMsgIter);

        //rtdData.reserve(totalSize);

        DBusMessageIter structIter;

        while(dbus_message_iter_get_arg_type(&dbusMsgIter) == DBUS_TYPE_STRUCT) {
            Rtd::RtdData rtd;
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
                rtd.quality = value.u64;
            }

            dbus_message_iter_next(&structIter);
            dbus_message_iter_get_basic(&structIter, &value);
            int typeValue = dbus_message_iter_get_arg_type(&structIter);
            switch(typeValue) {
                case DBUS_TYPE_BOOLEAN:
                    {
                        rtd.value.vt = Rtd::ValueType_Bool;
                        rtd.value.boolVal = value.i16 > 0;
                    }
                    break;
                case DBUS_TYPE_INT16:
                    {
                        rtd.value.vt = Rtd::ValueType_I2;
                        rtd.value.i2Val = value.i16;
                    }
                    break;
                case DBUS_TYPE_INT32:
                    {
                        rtd.value.vt = Rtd::ValueType_I4;
                        rtd.value.i4Val = value.i32;
                    }
                    break;
                case DBUS_TYPE_INT64:
                    {
                        rtd.value.vt = Rtd::ValueType_Bool;
                        rtd.value.i8Val = value.i64;
                    }
                    break;
                case DBUS_TYPE_UINT16:
                    {
                        rtd.value.vt = Rtd::ValueType_UI2;
                        rtd.value.ui2Val = value.u16;
                    }
                    break;
                case DBUS_TYPE_UINT32:
                    {
                        rtd.value.vt = Rtd::ValueType_UI4;
                        rtd.value.ui4Val = value.u32;
                    }
                    break;
                case DBUS_TYPE_UINT64:
                    {
                        rtd.value.vt = Rtd::ValueType_UI8;
                        rtd.value.ui8Val = value.u64;
                    }
                    break;
                case DBUS_TYPE_DOUBLE:
                    {
                        rtd.value.vt = Rtd::ValueType_Double;
                        rtd.value.dblVal = value.dbl;
                    }
                    break;
            }

            rtdData.push_back(rtd);
            dbus_message_iter_next(&dbusMsgIter);
        }

        return true;
    }
}