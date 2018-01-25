#include "rtdcollector/rtdCollector.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	Rtd::RtdCollector* pCollector = GetCollector();

	pCollector->initialize(nullptr);

	pCollector->start();

	Rtd::Value val;
	val.vt = Rtd::ValueType_I4;
	val.i4Val = 128;
	Rtd::RtdDataDeque dataDeque;
	Rtd::RtdData d1(1,0, val);
	dataDeque.push_back(d1);

	std::string value;
	do
	{
		std::getline(std::cin, value);

		pCollector->pushRtdData(dataDeque);

	} while (value.compare("Q") != 0);

	pCollector->stop();

	pCollector->uninitialize();
}