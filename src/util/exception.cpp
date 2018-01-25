//
// port from poco-1.8.1
//


#include "util/exception.h"
#include <typeinfo>


namespace Util {


Exception::Exception(int code): _pNested(0), _code(code)
{
}


Exception::Exception(const std::string& msg, int code): _msg(msg), _pNested(0), _code(code)
{
}


Exception::Exception(const std::string& msg, const std::string& arg, int code): _msg(msg), _pNested(0), _code(code)
{
	if (!arg.empty())
	{
		_msg.append(": ");
		_msg.append(arg);
	}
}


Exception::Exception(const std::string& msg, const Exception& nested, int code): _msg(msg), _pNested(nested.clone()), _code(code)
{
}


Exception::Exception(const Exception& exc):
	std::exception(exc),
	_msg(exc._msg),
	_code(exc._code)
{
	_pNested = exc._pNested ? exc._pNested->clone() : 0;
}

	
Exception::~Exception() throw()
{
	delete _pNested;
}


Exception& Exception::operator = (const Exception& exc)
{
	if (&exc != this)
	{
		Exception* newPNested = exc._pNested ? exc._pNested->clone() : 0;
		delete _pNested;
		_msg     = exc._msg;
		_pNested = newPNested;
		_code    = exc._code;
	}
	return *this;
}


const char* Exception::name() const throw()
{
	return "Exception";
}


const char* Exception::className() const throw()
{
	return typeid(*this).name();
}

	
const char* Exception::what() const throw()
{
	return name();
}

	
std::string Exception::displayText() const
{
	std::string txt = name();
	if (!_msg.empty())
	{
		txt.append(": ");
		txt.append(_msg);
	}
	return txt;
}


void Exception::extendedMessage(const std::string& arg)
{
	if (!arg.empty())
	{
		if (!_msg.empty()) _msg.append(": ");
		_msg.append(arg);
	}
}


Exception* Exception::clone() const
{
	return new Exception(*this);
}


void Exception::rethrow() const
{
	throw *this;
}


UTIL_IMPLEMENT_EXCEPTION(LogicException, Exception, "Logic exception")
UTIL_IMPLEMENT_EXCEPTION(AssertionViolationException, LogicException, "Assertion violation")
UTIL_IMPLEMENT_EXCEPTION(NullPointerException, LogicException, "Null pointer")
UTIL_IMPLEMENT_EXCEPTION(NullValueException, LogicException, "Null value")
UTIL_IMPLEMENT_EXCEPTION(BugcheckException, LogicException, "Bugcheck")
UTIL_IMPLEMENT_EXCEPTION(InvalidArgumentException, LogicException, "Invalid argument")
UTIL_IMPLEMENT_EXCEPTION(NotImplementedException, LogicException, "Not implemented")
UTIL_IMPLEMENT_EXCEPTION(RangeException, LogicException, "Out of range")
UTIL_IMPLEMENT_EXCEPTION(IllegalStateException, LogicException, "Illegal state")
UTIL_IMPLEMENT_EXCEPTION(InvalidAccessException, LogicException, "Invalid access")
UTIL_IMPLEMENT_EXCEPTION(SignalException, LogicException, "Signal received")
UTIL_IMPLEMENT_EXCEPTION(UnhandledException, LogicException, "Unhandled exception")

UTIL_IMPLEMENT_EXCEPTION(RuntimeException, Exception, "Runtime exception")
UTIL_IMPLEMENT_EXCEPTION(NotFoundException, RuntimeException, "Not found")
UTIL_IMPLEMENT_EXCEPTION(ExistsException, RuntimeException, "Exists")
UTIL_IMPLEMENT_EXCEPTION(TimeoutException, RuntimeException, "Timeout")
UTIL_IMPLEMENT_EXCEPTION(SystemException, RuntimeException, "System exception")
UTIL_IMPLEMENT_EXCEPTION(RegularExpressionException, RuntimeException, "Error in regular expression")
UTIL_IMPLEMENT_EXCEPTION(LibraryLoadException, RuntimeException, "Cannot load library")
UTIL_IMPLEMENT_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException, "Library already loaded")
UTIL_IMPLEMENT_EXCEPTION(NoThreadAvailableException, RuntimeException, "No thread available")
UTIL_IMPLEMENT_EXCEPTION(PropertyNotSupportedException, RuntimeException, "Property not supported")
UTIL_IMPLEMENT_EXCEPTION(PoolOverflowException, RuntimeException, "Pool overflow")
UTIL_IMPLEMENT_EXCEPTION(NoPermissionException, RuntimeException, "No permission")
UTIL_IMPLEMENT_EXCEPTION(OutOfMemoryException, RuntimeException, "Out of memory")
UTIL_IMPLEMENT_EXCEPTION(DataException, RuntimeException, "Data error")

UTIL_IMPLEMENT_EXCEPTION(DataFormatException, DataException, "Bad data format")
UTIL_IMPLEMENT_EXCEPTION(SyntaxException, DataException, "Syntax error")
UTIL_IMPLEMENT_EXCEPTION(CircularReferenceException, DataException, "Circular reference")
UTIL_IMPLEMENT_EXCEPTION(PathSyntaxException, SyntaxException, "Bad path syntax")
UTIL_IMPLEMENT_EXCEPTION(IOException, RuntimeException, "I/O error")
UTIL_IMPLEMENT_EXCEPTION(ProtocolException, IOException, "Protocol error")
UTIL_IMPLEMENT_EXCEPTION(FileException, IOException, "File access error")
UTIL_IMPLEMENT_EXCEPTION(FileExistsException, FileException, "File exists")
UTIL_IMPLEMENT_EXCEPTION(FileNotFoundException, FileException, "File not found")
UTIL_IMPLEMENT_EXCEPTION(PathNotFoundException, FileException, "Path not found")
UTIL_IMPLEMENT_EXCEPTION(FileReadOnlyException, FileException, "File is read-only")
UTIL_IMPLEMENT_EXCEPTION(FileAccessDeniedException, FileException, "Access to file denied")
UTIL_IMPLEMENT_EXCEPTION(CreateFileException, FileException, "Cannot create file")
UTIL_IMPLEMENT_EXCEPTION(OpenFileException, FileException, "Cannot open file")
UTIL_IMPLEMENT_EXCEPTION(WriteFileException, FileException, "Cannot write file")
UTIL_IMPLEMENT_EXCEPTION(ReadFileException, FileException, "Cannot read file")
UTIL_IMPLEMENT_EXCEPTION(DirectoryNotEmptyException, FileException, "Directory not empty")
UTIL_IMPLEMENT_EXCEPTION(UnknownURISchemeException, RuntimeException, "Unknown URI scheme")
UTIL_IMPLEMENT_EXCEPTION(TooManyURIRedirectsException, RuntimeException, "Too many URI redirects")
UTIL_IMPLEMENT_EXCEPTION(URISyntaxException, SyntaxException, "Bad URI syntax")

UTIL_IMPLEMENT_EXCEPTION(ApplicationException, Exception, "Application exception")
UTIL_IMPLEMENT_EXCEPTION(BadCastException, RuntimeException, "Bad cast exception")


} // namespace Util
