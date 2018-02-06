#ifndef __RTD_MESSAGE_H_1656__
#define __RTD_MESSAGE_H_1656__

#include "rtd/rtdInfo.h"
#include <dbus/dbus.h>

namespace RtdDBus
{
	bool decodeSubscribe(DBusMessage* dbusMessage, Rtd::RtdTagDeque& tags);

	bool decodeUnsubscribe(DBusMessage* dbusMessage, Rtd::RtdTagIDDeque& tagIDs);
}

#endif // __RTD_MESSAGE_H_1656__
