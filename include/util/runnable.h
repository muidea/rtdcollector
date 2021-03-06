//
// port from poco-1.8.1
//


#ifndef __RUNNABLE_H_1407__
#define __RUNNABLE_H_1407__


#include "util.h"


namespace Util {


class Util_API Runnable
	/// The Runnable interface with the run() method
	/// must be implemented by classes that provide
	/// an entry point for a thread.
{
public:	
	Runnable();
	virtual ~Runnable();
	
	virtual void run() = 0;
		/// Do whatever the thread needs to do. Must
		/// be overridden by subclasses.
};


} // namespace Util


#endif // __RUNNABLE_H_1407__
