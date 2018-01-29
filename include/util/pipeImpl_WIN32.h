//
// port from poco-1.8.1
//


#ifndef __PIPEIMPL_WIN32_H_1355__
#define __PIPEIMPL_WIN32_H_1355__


#include "util.h"
#include "refCountedObject.h"
#include "unWindows.h"

namespace Util {


class Util_API PipeImpl: public RefCountedObject
	/// A dummy implementation of PipeImpl for platforms
	/// that do not support pipes.
{
public:
	typedef HANDLE Handle;

	PipeImpl();
	~PipeImpl();
	int writeBytes(const void* buffer, int length);
	int readBytes(void* buffer, int length);
	Handle readHandle() const;
	Handle writeHandle() const;
	void closeRead();
	void closeWrite();
	
private:
	HANDLE _readHandle;
	HANDLE _writeHandle;
};


} // namespace Util


#endif // __PIPEIMPL_WIN32_H_1355__
