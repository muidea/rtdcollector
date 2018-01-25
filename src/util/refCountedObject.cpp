//
// port from poco-1.8.1
//



#include "util/refCountedObject.h"


namespace Util {


RefCountedObject::RefCountedObject(): _counter(1)
{
}


RefCountedObject::~RefCountedObject()
{
}


} // namespace Util
