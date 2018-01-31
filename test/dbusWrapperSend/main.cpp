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

	} while (value.compare("Q") != 0);

	pEndPoint->unregisterEndPoint();

	pEndPoint->release();

	return 0;
}