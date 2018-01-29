//
// port from poco-1.8.1
//


#ifndef __PIPEIMPL_POSIX_H_1355__
#define __PIPEIMPL_POSIX_H_1355__


#include "util.h"
#include "refCountedObject.h"


namespace Util {


class Util_API PipeImpl: public RefCountedObject
	/// A dummy implementation of PipeImpl for platforms
	/// that do not support pipes.
{
public:
	typedef int Handle;

	PipeImpl();
	~PipeImpl();
	int writeBytes(const void* buffer, int length);
	int readBytes(void* buffer, int length);
	Handle readHandle() const;
	Handle writeHandle() const;
	void closeRead();
	void closeWrite();
	
private:
	int _readfd;
	int _writefd;
};


} // namespace Util


#endif // __PIPEIMPL_POSIX_H_1355__
