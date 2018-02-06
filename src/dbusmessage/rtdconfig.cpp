#include "dbusmessage/rtdconfig.h"
#include "tinyxml2/tinyxml2.h"

namespace RtdDBus
{
	void encodeElement(DBusMessageIter dbusMsgIter, tinyxml2::XMLElement* pElement)
	{
		if (pElement == nullptr) {
			return;
		}

		DBusMessageIter structIter;
		dbus_message_iter_open_container(&dbusMsgIter, DBUS_TYPE_STRUCT, 0, &structIter);

		const char* tagName = pElement->Attribute("tagnanme");
		const char* tagDescription = pElement->Attribute("description");
		int tagType = pElement->IntAttribute("datatype");
		if (tagName) {
			dbus_message_iter_append_basic(&structIter, DBUS_TYPE_STRING, &tagName);
		}
		if (tagDescription) {
			dbus_message_iter_append_basic(&structIter, DBUS_TYPE_STRING, &tagDescription);
		}

		if (tagType == Rtd::ValueType_Object) {
			auto subElement = pElement->FirstChildElement();
			do
			{
				if (subElement == nullptr) {
					break;
				}

				encodeElement(dbusMsgIter, subElement);
				subElement = subElement->NextSiblingElement();
			} while (true);
		}
		else {
			dbus_message_iter_append_basic(&structIter, DBUS_TYPE_INT16, &tagType);
		}

		dbus_message_iter_close_container(&dbusMsgIter, &structIter);
	}

    bool encodeRtdConfig(Rtd::ConfigInfo const& rtdConfig, DBusMessage* dbusMsg)
    {
        DBusMessageIter dbusMsgIter;
        dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);

		auto root = rtdConfig->RootElement();
		if (root == nullptr) {
			return false;
		}

		auto subElement = root->FirstChildElement();
		do 
		{
			if (subElement != nullptr) {
				break;
			}

			encodeElement(dbusMsgIter, subElement);

			subElement = subElement->NextSiblingElement();
		} while (true);

		return true;
    }
    
    bool decodeRtdConfig(DBusMessage* dbusMsg, Rtd::ConfigInfo& rtdConfig)
    {
        DBusMessageIter dbusMsgIter;
        DBusBasicValue value;
        dbus_message_iter_init(dbusMsg,&dbusMsgIter);

        if (dbus_message_iter_get_arg_type(&dbusMsgIter)!= DBUS_TYPE_STRING) {
            return false;
        }
        
        dbus_message_iter_get_basic(&dbusMsgIter,&value);
        return true;
    }
}