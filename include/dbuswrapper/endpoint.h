#ifndef __ENDPOINT_H_1645__
#define  __ENDPOINT_H_1645__
#include "def.h"
#include <dbus/dbus.h>
#include <string>

namespace DBusWrapper
{
	typedef std::string Message;
	typedef std::string Addr;

	class EndPointCallBack
	{
	public:
		virtual ~EndPointCallBack() {}

		virtual void onMessage(Message const& msg) = 0;
	};

	class EndPoint
	{
	public:
		virtual void registerEndPoint(std::string const& endPointName) = 0;

		virtual void unregisterEndPoint() = 0;

		virtual void sendMessage(Message const& msg) = 0;

		virtual void postMessage(DBusMessage* dbusMsg) = 0;

		virtual void sendMessage(DBusMessage* dbusMsg) = 0;

		virtual void release() = 0;

	protected:
		EndPoint() {};
		virtual ~EndPoint() {};
	};

}

DBusWrapper_API DBusWrapper::EndPoint* GetEndPoint(std::string const& nameSpace, DBusWrapper::EndPointCallBack* pCallBack);


#endif //  __ENDPOINT_H_1645__
