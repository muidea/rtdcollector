#include "dbusmessage/rtdconfig.h"
#include "tinyxml2/tinyxml2.h"

namespace RtdDBus
{
	const std::string tag = "tag";
	void encodeElement(DBusMessageIter& dbusMsgIter, tinyxml2::XMLElement* pElement)
	{
		if (pElement == nullptr) {
			return;
		}

		DBusMessageIter structIter;
		dbus_message_iter_open_container(&dbusMsgIter, DBUS_TYPE_STRUCT, 0, &structIter);

		const char* tagName = pElement->Attribute("tagname");
		const char* tagDescription = pElement->Attribute("description");
		int tagType = pElement->IntAttribute("datatype");
		if (tagName) {
			dbus_message_iter_append_basic(&structIter, DBUS_TYPE_STRING, &tagName);
		}
		if (tagDescription) {
			dbus_message_iter_append_basic(&structIter, DBUS_TYPE_STRING, &tagDescription);
		}

		dbus_message_iter_append_basic(&structIter, DBUS_TYPE_INT32, &tagType);
		if (tagType == Rtd::ValueType_Object) {
			auto subElement = pElement->FirstChildElement(tag.c_str());
			do {
				if (subElement == nullptr) {
					break;
				}

				encodeElement(structIter, subElement);
				subElement = subElement->NextSiblingElement(tag.c_str());
			} while (true);
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

		auto subElement = root->FirstChildElement(tag.c_str());
		do {
			if (subElement == nullptr) {
				break;
			}

			encodeElement(dbusMsgIter, subElement);

			subElement = subElement->NextSiblingElement(tag.c_str());
		} while (true);

		return true;
	}

	bool decodeStruct(DBusMessageIter& msgIter, tinyxml2::XMLDocument* pDoc, tinyxml2::XMLElement* pElement)
	{
		DBusBasicValue value;
		if (dbus_message_iter_get_arg_type(&msgIter) == DBUS_TYPE_STRING) {
			dbus_message_iter_get_basic(&msgIter, &value);
			pElement->SetAttribute("tagname", value.str);
		}

		if (dbus_message_iter_get_arg_type(&msgIter) == DBUS_TYPE_STRING) {
			dbus_message_iter_get_basic(&msgIter, &value);
			pElement->SetAttribute("description", value.str);
		}
		if (dbus_message_iter_get_arg_type(&msgIter) == DBUS_TYPE_INT32) {
			dbus_message_iter_get_basic(&msgIter, &value);
			pElement->SetAttribute("datatype", value.i32);
		}
		if (value.i32 == Rtd::ValueType_Object) {
			DBusMessageIter structIter;
			dbus_message_iter_recurse(&msgIter, &structIter);
			while(dbus_message_iter_get_arg_type(&structIter) == DBUS_TYPE_STRUCT) {
				tinyxml2::XMLElement* pSubElement = pDoc->NewElement(tag.c_str());
				pElement->InsertEndChild(pSubElement);
				decodeStruct(structIter, pDoc, pSubElement);

				dbus_message_iter_next(&structIter);
			}
		}
	}

	bool decodeRtdConfig(DBusMessage* dbusMsg, Rtd::ConfigInfo& rtdConfig)
	{
		DBusMessageIter dbusMsgIter;
		dbus_message_iter_init(dbusMsg, &dbusMsgIter);

		DBusMessageIter structIter;
		while(dbus_message_iter_get_arg_type(&dbusMsgIter) == DBUS_TYPE_STRUCT) {
			tinyxml2::XMLElement* pElement = rtdConfig->NewElement(tag.c_str());
			decodeStruct(dbusMsgIter, rtdConfig, pElement);
			dbus_message_iter_next(&dbusMsgIter);
		}

		return true;
	}
}