#include "dbuswrapper/endpoint.h"
#include <iostream>
#include <string>

class EndPointCallBackImpl : public DBusWrapper::EndPointCallBack
{
public:
	virtual void onMessage(DBusMessage* dbusMsg)
	{
		//std::cout << "recv message:" << msg << std::endl;
	}
};


int main(int argc, char ** argv)
{
	EndPointCallBackImpl impl;
	std::string nameSpace("com.supos.shuttle.drivermanager");
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