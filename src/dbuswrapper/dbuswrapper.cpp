#include "dbuswrapper.h"
#include <sstream>
#include <iostream>

namespace DBusWrapper
{
	const std::string MessagePath = "/com/supos/shuttle/drivermanager";
	const std::string MessageName = "RtMessage";

	DBusWrapper::DBusWrapper(std::string const& nameSpace)
		: m_connection(nullptr)
		, m_scopeNameSpace(nameSpace)
	{
		dbus_error_init(&m_err);
	}

	DBusWrapper::~DBusWrapper()
	{
		if (m_connection) {
			uninitialize();
		}

		dbus_error_free(&m_err);
	}

	void DBusWrapper::initialize(std::string const& localName)
	{
		m_connection = dbus_bus_get(DBUS_BUS_SESSION, &m_err);
		if (dbus_error_is_set(&m_err)) {
			std::cout << "dbus_bus_get failed" << std::endl;
		}

		int ret = dbus_bus_request_name(m_connection, localName.c_str(), DBUS_NAME_FLAG_REPLACE_EXISTING, &m_err);
		if (-1 == ret && dbus_error_is_set(&m_err)) {
			std::cout << "dbus_bus_request_name failed, localName:" << localName << std::endl;
		}

		std::stringstream oss;
		oss << "type='signal',interface='" << m_scopeNameSpace << "'";
		dbus_bus_add_match(m_connection, oss.str().c_str(), &m_err);
		if (dbus_error_is_set(&m_err)) {
			std::cout << "dbus_bus_add_match failed, oss:" << oss.str() << std::endl;
		}
		dbus_connection_flush(m_connection);

	}

	void DBusWrapper::uninitialize()
	{
		if (m_connection) {
			dbus_bus_remove_match(m_connection, m_scopeNameSpace.c_str(), &m_err);
			if (dbus_error_is_set(&m_err)) {

			}
			dbus_connection_flush(m_connection);

			dbus_connection_unref(m_connection);
			m_connection = nullptr;
		}
	}

	void DBusWrapper::sendMessage(std::string const& msg)
	{
		DBusMessage* dbusMsg = dbus_message_new_signal(MessagePath.c_str(), m_scopeNameSpace.c_str(), MessageName.c_str());
		if (dbusMsg) {
			DBusMessageIter dbusMsgIter;
			dbus_message_iter_init_append(dbusMsg, &dbusMsgIter);
			if (!dbus_message_iter_append_basic(&dbusMsgIter, DBUS_TYPE_STRING, msg.c_str())) {

			}

			if (!dbus_connection_send(m_connection, dbusMsg, NULL)) {

			}
			dbus_connection_flush(m_connection);
			dbus_message_unref(dbusMsg);
		}
		else {

		}
	}

	bool DBusWrapper::recvMessage(std::string& msg)
	{
		DBusMessage* dbusMsg = dbus_connection_pop_message(m_connection);
		DBusMessageIter dbusMsgIter;
		DBusBasicValue value;

		if (dbusMsg) {
			if (dbus_message_is_signal(dbusMsg, m_scopeNameSpace.c_str(), MessageName.c_str())) {
				if (!dbus_message_iter_init(dbusMsg, &dbusMsgIter)){
					std::cout << "MessageHas no Param" << std::endl;
				}

				if (dbus_message_iter_get_arg_type(&dbusMsgIter) != DBUS_TYPE_STRING) {
					std::cout << "Param isnot string" << std::endl;
				}

				dbus_message_iter_get_basic(&dbusMsgIter, &value);

				msg.assign(value.str);
				if (msg.size() > 0) {
					std::cout << msg << std::endl;
				}
			} else {
				std::cout << "dbus_message_is_signal failed" << std::endl;
			}

			dbus_message_unref(dbusMsg);
		} else {
			std::cout << "dbus_connection_pop_message failed" << std::endl;
		}
	}

	bool DBusWrapper::isAvailable() const
	{
		if (m_connection) {
			return dbus_connection_read_write(m_connection, 0);
		}

		return false;
	}

}
