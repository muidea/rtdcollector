#include "dbusmessage/rtdmessage.h"

namespace RtdDBus
{
	bool decodeSubscribe(DBusMessage* dbusMessage, Rtd::RtdTagDeque& tags)
	{
		DBusMessageIter dbusMsgIter;
		DBusBasicValue value;
		dbus_message_iter_init(dbusMessage, &dbusMsgIter);

		DBusMessageIter structIter;
		while (dbus_message_iter_get_arg_type(&dbusMsgIter) == DBUS_TYPE_STRUCT) {
			Rtd::RtdTag tag;
			dbus_message_iter_recurse(&dbusMsgIter, &structIter);
			if (dbus_message_iter_get_arg_type(&structIter) == DBUS_TYPE_STRING) {
				dbus_message_iter_get_basic(&structIter, &value);
				tag.tagName.assign(value.str);
			}

			dbus_message_iter_next(&structIter);
			if (dbus_message_iter_get_arg_type(&structIter) == DBUS_TYPE_UINT64) {
				dbus_message_iter_get_basic(&structIter, &value);
				tag.tagID = value.u64;
			}

			tags.push_back(tag);
			dbus_message_iter_next(&dbusMsgIter);
		}

		return true;
	}

	bool decodeUnsubscribe(DBusMessage* dbusMessage, Rtd::RtdTagIDDeque& tagIDs)
	{
		DBusMessageIter dbusMsgIter;
		DBusBasicValue value;
		dbus_message_iter_init(dbusMessage, &dbusMsgIter);

		DBusMessageIter structIter;
		while (dbus_message_iter_get_arg_type(&dbusMsgIter) == DBUS_TYPE_STRUCT) {
			Rtd::RtdTag tag;
			dbus_message_iter_recurse(&dbusMsgIter, &structIter);
			if (dbus_message_iter_get_arg_type(&structIter) == DBUS_TYPE_UINT64) {
				dbus_message_iter_get_basic(&structIter, &value);
				tagIDs.push_back(value.u64);
			}

			dbus_message_iter_next(&dbusMsgIter);
		}

		return true;
	}
}