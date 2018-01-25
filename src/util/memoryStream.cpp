//
// port from poco-1.8.1
//


#include "util/memoryStream.h"


namespace Util {


MemoryIOS::MemoryIOS(char* pBuffer, std::streamsize bufferSize):
	_buf(pBuffer, bufferSize)
{
	util_ios_init(&_buf);
}


MemoryIOS::~MemoryIOS()
{
}


MemoryInputStream::MemoryInputStream(const char* pBuffer, std::streamsize bufferSize): 
	MemoryIOS(const_cast<char*>(pBuffer), bufferSize), 
	std::istream(&_buf)
{
}


MemoryInputStream::~MemoryInputStream()
{
}


MemoryOutputStream::MemoryOutputStream(char* pBuffer, std::streamsize bufferSize): 
	MemoryIOS(pBuffer, bufferSize), 
	std::ostream(&_buf)
{
}


MemoryOutputStream::~MemoryOutputStream()
{
}


} // namespace Util
