#include "dbuswrapper.h"
#include "util/exception.h"
#include <sstream>

namespace DBusWrapper
{
	const std::string MessagePath = "/com/supos/shuttle/drivermanager";
	const std::string MessageName = "RtMessage";

	DBusWrapper::DBusWrapper(std::string const& interface, DBusWrapperSink* pSink)
		: m_connection(nullptr)
		, m_interface(interface)
		, m_pSink(pSink)
	{
		std::stringstream sigalOss;
		sigalOss << "type='signal',interface='" << m_interface << "'";
		m_signalRule = sigalOss.str();

		std::stringstream methodOss;
		methodOss << "type='method_call',interface='" << m_interface << "'";
		m_methodRule = methodOss.str();

		dbus_threads_init_default();

		dbus_error_init(&m_err);
	}

	DBusWrapper::~DBusWrapper()
	{
		if (m_connection) {
			uninitialize();
		}

		dbus_error_free(&m_err);

		dbus_shutdown();
	}

	void DBusWrapper::initialize(std::string const& localName)
	{
		m_connection = dbus_bus_get(DBUS_BUS_SESSION, &m_err);
		if (dbus_error_is_set(&m_err)) {
			std::stringstream oss;
			oss << "dbus_bus_get failed, err:" << m_err.message << std::endl;
			throw Util::SystemException(oss.str());
		}

		int ret = dbus_bus_request_name(m_connection, localName.c_str(), DBUS_NAME_FLAG_REPLACE_EXISTING, &m_err);
		if (-1 == ret && dbus_error_is_set(&m_err)) {
			std::stringstream oss;
			oss << "dbus_bus_request_name failed, err:" << m_err.message << std::endl;
			throw Util::SystemException(oss.str());
		}

		dbus_bus_add_match(m_connection, m_signalRule.c_str(), &m_err);
		if (dbus_error_is_set(&m_err)) {
			std::stringstream oss;
			oss << "dbus_bus_add_match failed, err:" << m_err.message << std::endl;
			throw Util::SystemException(oss.str());
		}

		dbus_bus_add_match(m_connection, m_methodRule.c_str(), &m_err);
		if (dbus_error_is_set(&m_err)) {
			std::stringstream oss;
			oss << "dbus_bus_add_match failed, err:" << m_err.message << std::endl;
			throw Util::SystemException(oss.str());
		}

		dbus_connection_flush(m_connection);
	}

	void DBusWrapper::uninitialize()
	{
		if (m_connection) {
			dbus_bus_remove_match(m_connection, m_signalRule.c_str(), &m_err);
			if (dbus_error_is_set(&m_err)) {
				std::stringstream oss;
				oss << "dbus_bus_remove_match failed, err:" << m_err.message << std::endl;
				throw Util::SystemException(oss.str());
			}
			dbus_bus_remove_match(m_connection, m_methodRule.c_str(), &m_err);
			if (dbus_error_is_set(&m_err)) {
				std::stringstream oss;
				oss << "dbus_bus_remove_match failed, err:" << m_err.message << std::endl;
				throw Util::SystemException(oss.str());
			}

			dbus_connection_flush(m_connection);

			dbus_connection_unref(m_connection);
			m_connection = nullptr;
		}
	}

	DBusMessage* DBusWrapper::sendMessage(DBusMessage* dbusMsg)
	{
		DBusMessage* pReply = dbus_connection_send_with_reply_and_block(m_connection, dbusMsg, -1, &m_err);
		if (dbus_error_is_set(&m_err)) {
			std::stringstream oss;
			oss << "dbus_connection_send_with_reply_and_block failed, err:" << m_err.message << std::endl;
			throw Util::SystemException(oss.str());
		}

		dbus_message_unref(dbusMsg);

		return pReply;
	}

	void DBusWrapper::postMessage(DBusMessage* dbusMsg)
	{
		dbus_uint32_t  serial = 0;
		if (!dbus_connection_send(m_connection, dbusMsg, &serial)) {
			std::stringstream oss;
			oss << "dbus_connection_send failed, err:" << m_err.message << std::endl;
			throw Util::SystemException(oss.str());
		}
		dbus_connection_flush(m_connection);
		dbus_message_unref(dbusMsg);
	}

	bool DBusWrapper::recvMessage()
	{
		DBusMessage* dbusMsg = dbus_connection_pop_message(m_connection);
		if (dbusMsg && m_pSink) {
			m_pSink->onRecvMessage(dbusMsg);
		}

		return dbusMsg != nullptr;
	}

	bool DBusWrapper::isAvailable() const
	{
		if (m_connection) {
			return dbus_connection_read_write(m_connection, 0);
		}

		return false;
	}

}
