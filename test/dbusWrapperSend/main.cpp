#include "dbuswrapper/endpoint.h"
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
	std::string nameSpace("com.supos.shuttle.drivermanager");
	DBusWrapper::EndPoint* pEndPoint = GetEndPoint(nameSpace, NULL);

	pEndPoint->registerEndPoint("com.supos.shuttle.drivermanager.send");

	std::string value;
	do
	{
		std::getline(std::cin, value);

		const char* ptr = value.c_str();
		DBusMessage* msg = dbus_message_new_signal("/com/supos/shuttle/drivermanager/demo", nameSpace.c_str(), "test");
		DBusMessageIter msgIter;
		dbus_message_iter_init_append(msg, &msgIter);		
		dbus_message_iter_append_basic(&msgIter, DBUS_TYPE_STRING, &ptr);

		pEndPoint->postMessage(msg);
	} while (value.compare("Q") != 0);

	pEndPoint->unregisterEndPoint();

	pEndPoint->release();

	return 0;
}