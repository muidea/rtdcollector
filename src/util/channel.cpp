//
// port from poco-1.8.1
//


#include "util/channel.h"


namespace Util {


Channel::Channel()
{
}


Channel::~Channel()
{
}


void Channel::open()
{
}


void Channel::close()
{
}


void Channel::setProperty(const std::string& name, const std::string& value)
{
	throw PropertyNotSupportedException(name);
}


std::string Channel::getProperty(const std::string& name) const
{
	throw PropertyNotSupportedException(name);
}


} // namespace Util
