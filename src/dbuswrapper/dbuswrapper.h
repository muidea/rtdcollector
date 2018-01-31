#ifndef __DBUS_WRAPPER_H_1354__
#define __DBUS_WRAPPER_H_1354__
#include <dbus/dbus.h>
#include <string>

namespace DBusWrapper
{
	class DBusWrapper
	{
	public:
		DBusWrapper(std::string const& nameSpace);

		~DBusWrapper();

		void initialize(std::string const& localName);

		void uninitialize();

		void sendMessage(std::string const& msg);

		bool recvMessage(std::string& msg);

		bool isAvailable() const;

	protected:
		std::string m_scopeNameSpace;

		DBusError m_err;
		DBusConnection* m_connection;
	};
}

#endif