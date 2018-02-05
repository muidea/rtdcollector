#include "dbuswrapper/endpoint.h"
#include <iostream>
#include <string>

std::string nameSpace("com.supos.shuttle.drivermanager");

class EndPointCallBackImpl : public DBusWrapper::EndPointCallBack
{
public:
	virtual void onMessage(DBusMessage* dbusMsg)
	{
		if (dbus_message_is_signal(dbusMsg, nameSpace.c_str(), "test")) {
			DBusMessageIter dbusMsgIter;
			DBusBasicValue value;
			dbus_message_iter_init(dbusMsg,&dbusMsgIter);

			if (dbus_message_iter_get_arg_type(&dbusMsgIter)!= DBUS_TYPE_STRING) {
				return;
			}
			
			dbus_message_iter_get_basic(&dbusMsgIter,&value);
			
			std::cout << "recvMsg:" << value.str << std::endl;
		}
	}
};


int main(int argc, char ** argv)
{
	EndPointCallBackImpl impl;
	DBusWrapper::EndPoint* pEndPoint = GetEndPoint(nameSpace, &impl);

	pEndPoint->registerEndPoint("com.supos.shuttle.drivermanager.recv");

	std::string value;
	do
	{
		std::getline(std::cin, value);

	} while (value.compare("Q") != 0);

	pEndPoint->unregisterEndPoint();

	pEndPoint->release();

	return 0;
}