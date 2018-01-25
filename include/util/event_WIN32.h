//
// port from poco-1.8.1
//


#ifndef __EVENT_WIN32_H_1342__
#define __EVENT_WIN32_H_1342__


#include "util.h"
#include "exception.h"
#include "unWindows.h"


namespace Util {


class Util_API EventImpl
{
protected:
	EventImpl(bool autoReset);		
	~EventImpl();
	void setImpl();
	void waitImpl();
	bool waitImpl(long milliseconds);
	void resetImpl();
	
private:
	HANDLE _event;
};


//
// inlines
//
inline void EventImpl::setImpl()
{
	if (!SetEvent(_event))
	{
		throw SystemException("cannot signal event");
	}
}


inline void EventImpl::resetImpl()
{
	if (!ResetEvent(_event))
	{
		throw SystemException("cannot reset event");
	}
}


} // namespace Util


#endif // __EVENT_WIN32_H_1342__
