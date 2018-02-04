#include "dbusmessage/rtdconfig.h"
#include "tinyxml2/tinyxml2.h"

namespace RtdDBus
{
    bool encodeRtdConfig(Rtd::ConfigInfo const& rtdConfig, DBusMessage* dbusMsg)
    {
        DBusMessageIter dbusMsgIter;
        dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);

        tinyxml2::XMLPrinter printer;
        rtdConfig->Print(&printer);
        const char* pPtr = printer.CStr();

        return dbus_message_iter_append_basic(&dbusMsgIter, DBUS_TYPE_STRING, &pPtr);
    }
    
}