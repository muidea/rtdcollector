//
// port from poco-1.8.1
//


#include "util/pipeImpl_WIN32.h"
#include "util/exception.h"


namespace Util {


PipeImpl::PipeImpl()
{
	SECURITY_ATTRIBUTES attr;
	attr.nLength              = sizeof(attr);
	attr.lpSecurityDescriptor = NULL;
	attr.bInheritHandle       = FALSE;
	
	if (!CreatePipe(&_readHandle, &_writeHandle, &attr, 0))
		throw CreateFileException("anonymous pipe");
}


PipeImpl::~PipeImpl()
{
	closeRead();
	closeWrite();
}


int PipeImpl::writeBytes(const void* buffer, int length)
{
	util_assert (_writeHandle != INVALID_HANDLE_VALUE);

	DWORD bytesWritten = 0;
	if (!WriteFile(_writeHandle, buffer, length, &bytesWritten, NULL))
		throw WriteFileException("anonymous pipe");
	return bytesWritten;
}


int PipeImpl::readBytes(void* buffer, int length)
{
	util_assert (_readHandle != INVALID_HANDLE_VALUE);

	DWORD bytesRead = 0;
	BOOL ok = ReadFile(_readHandle, buffer, length, &bytesRead, NULL);
	if (ok || GetLastError() == ERROR_BROKEN_PIPE)
		return bytesRead;
	else
		throw ReadFileException("anonymous pipe");
}


PipeImpl::Handle PipeImpl::readHandle() const
{
	return _readHandle;
}


PipeImpl::Handle PipeImpl::writeHandle() const
{
	return _writeHandle;
}


void PipeImpl::closeRead()
{
	if (_readHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_readHandle);
		_readHandle = INVALID_HANDLE_VALUE;
	}
}


void PipeImpl::closeWrite()
{
	if (_writeHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_writeHandle);
		_writeHandle = INVALID_HANDLE_VALUE;
	}
}


} // namespace Util
