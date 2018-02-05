#ifndef __DBUS_WRAPPER_H_1354__
#define __DBUS_WRAPPER_H_1354__
#include <dbus/dbus.h>
#include <string>

namespace DBusWrapper
{
	class DBusWrapperSink
	{
		public:
		virtual ~DBusWrapperSink(){}

		virtual void onRecvMessage(DBusMessage* dbusMsg) = 0;
	};

	class DBusWrapper
	{
	public:
		DBusWrapper(std::string const& nameSpace, DBusWrapperSink* pSink);

		~DBusWrapper();

		void initialize(std::string const& localName);

		void uninitialize();
		
		bool recvMessage();

		DBusMessage* sendMessage(DBusMessage* dbusMsg);

		void postMessage(DBusMessage* dbusMsg);

		bool isAvailable() const;

	protected:
		std::string m_scopeNameSpace;
		std::string m_signalRule;
		std::string m_methodRule;

		DBusWrapperSink* m_pSink;

		DBusError m_err;
		DBusConnection* m_connection;
	};
}

#endif