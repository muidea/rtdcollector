//
// port from poco-1.8.1
//


#ifndef __RUNNABLEADAPTER_H_1408__
#define __RUNNABLEADAPTER_H_1408__


#include "util.h"
#include "runnable.h"


namespace Util {


template <class C>
class RunnableAdapter: public Runnable
	/// This adapter simplifies using ordinary methods as
	/// targets for threads.
	/// Usage:
	///    RunnableAdapter<MyClass> ra(myObject, &MyObject::doSomething));
	///    Thread thr;
	///    thr.Start(ra);
	///
	/// For using a freestanding or static member function as a thread
	/// target, please see the ThreadTarget class.
{
public:
	typedef void (C::*Callback)();
	
	RunnableAdapter(C& object, Callback method): _pObject(&object), _method(method)
	{
	}
	
	RunnableAdapter(const RunnableAdapter& ra): _pObject(ra._pObject), _method(ra._method)
	{
	}

	~RunnableAdapter()
	{
	}

	RunnableAdapter& operator = (const RunnableAdapter& ra)
	{
		_pObject = ra._pObject;
		_method  = ra._method;
		return *this;
	}

	void run()
	{
		(_pObject->*_method)();
	}
	
private:
	RunnableAdapter();

	C*       _pObject;
	Callback _method;
};


} // namespace Util


#endif // __RUNNABLEADAPTER_H_1408__
