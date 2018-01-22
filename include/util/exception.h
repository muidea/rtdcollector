//
// Exception.h
//
// Library: Foundation
// Package: Core
// Module:  Exception
//
// Definition of various Poco exception classes.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef __EXCEPTION_H_1652__
#define __EXCEPTION_H_1652__


#include "util.h"
#include <stdexcept>


namespace Util {


class Util_API Exception: public std::exception
	/// This is the base class for all exceptions defined
	/// in the Poco class library.
{
public:
	Exception(const std::string& msg, int code = 0);
		/// Creates an exception.

	Exception(const std::string& msg, const std::string& arg, int code = 0);
		/// Creates an exception.

	Exception(const std::string& msg, const Exception& nested, int code = 0);
		/// Creates an exception and stores a clone
		/// of the nested exception.

	Exception(const Exception& exc);
		/// Copy constructor.
		
	~Exception() throw();
		/// Destroys the exception and deletes the nested exception.

	Exception& operator = (const Exception& exc);
		/// Assignment operator.

	virtual const char* name() const throw();
		/// Returns a static string describing the exception.
		
	virtual const char* className() const throw();
		/// Returns the name of the exception class.
		
	virtual const char* what() const throw();
		/// Returns a static string describing the exception.
		///
		/// Same as name(), but for compatibility with std::exception.
		
	const Exception* nested() const;
		/// Returns a pointer to the nested exception, or
		/// null if no nested exception exists.
			
	const std::string& message() const;
		/// Returns the message text.
			
	int code() const;
		/// Returns the exception code if defined.
		
	std::string displayText() const;
		/// Returns a string consisting of the
		/// message name and the message text.

	virtual Exception* clone() const;
		/// Creates an exact copy of the exception.
		///
		/// The copy can later be thrown again by
		/// invoking rethrow() on it.
		
	virtual void rethrow() const;
		/// (Re)Throws the exception.
		///
		/// This is useful for temporarily storing a
		/// copy of an exception (see clone()), then
		/// throwing it again.

protected:
	Exception(int code = 0);
		/// Standard constructor.

	void message(const std::string& msg);
		/// Sets the message for the exception.

	void extendedMessage(const std::string& arg);
		/// Sets the extended message for the exception.
		
private:
	std::string _msg;
	Exception*  _pNested;
	int			_code;
};


//
// inlines
//
inline const Exception* Exception::nested() const
{
	return _pNested;
}


inline const std::string& Exception::message() const
{
	return _msg;
}


inline void Exception::message(const std::string& msg)
{
	_msg = msg;
}


inline int Exception::code() const
{
	return _code;
}


//
// Macros for quickly declaring and implementing exception classes.
// Unfortunately, we cannot use a template here because character
// pointers (which we need for specifying the exception name)
// are not allowed as template arguments.
//
#define UTIL_DECLARE_EXCEPTION_CODE(API, CLS, BASE, CODE) \
	class API CLS: public BASE														\
	{																				\
	public:																			\
		CLS(int code = CODE);														\
		CLS(const std::string& msg, int code = CODE);								\
		CLS(const std::string& msg, const std::string& arg, int code = CODE);		\
		CLS(const std::string& msg, const Util::Exception& exc, int code = CODE);	\
		CLS(const CLS& exc);														\
		~CLS() throw();																\
		CLS& operator = (const CLS& exc);											\
		const char* name() const throw();											\
		const char* className() const throw();										\
		Util::Exception* clone() const;												\
		void rethrow() const;														\
	};

#define UTIL_DECLARE_EXCEPTION(API, CLS, BASE) \
	UTIL_DECLARE_EXCEPTION_CODE(API, CLS, BASE, 0)

#define UTIL_IMPLEMENT_EXCEPTION(CLS, BASE, NAME)													\
	CLS::CLS(int code): BASE(code)																	\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, int code): BASE(msg, code)										\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, const std::string& arg, int code): BASE(msg, arg, code)		\
	{																								\
	}																								\
	CLS::CLS(const std::string& msg, const Util::Exception& exc, int code): BASE(msg, exc, code)	\
	{																								\
	}																								\
	CLS::CLS(const CLS& exc): BASE(exc)																\
	{																								\
	}																								\
	CLS::~CLS() throw()																				\
	{																								\
	}																								\
	CLS& CLS::operator = (const CLS& exc)															\
	{																								\
		BASE::operator = (exc);																		\
		return *this;																				\
	}																								\
	const char* CLS::name() const throw()															\
	{																								\
		return NAME;																				\
	}																								\
	const char* CLS::className() const throw()														\
	{																								\
		return typeid(*this).name();																\
	}																								\
	Util::Exception* CLS::clone() const																\
	{																								\
		return new CLS(*this);																		\
	}																								\
	void CLS::rethrow() const																		\
	{																								\
		throw *this;																				\
	}


//
// Standard exception classes
//
UTIL_DECLARE_EXCEPTION(Util_API, LogicException, Exception)
UTIL_DECLARE_EXCEPTION(Util_API, AssertionViolationException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, NullPointerException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, NullValueException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, BugcheckException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, InvalidArgumentException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, NotImplementedException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, RangeException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, IllegalStateException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, InvalidAccessException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, SignalException, LogicException)
UTIL_DECLARE_EXCEPTION(Util_API, UnhandledException, LogicException)

UTIL_DECLARE_EXCEPTION(Util_API, RuntimeException, Exception)
UTIL_DECLARE_EXCEPTION(Util_API, NotFoundException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, ExistsException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, TimeoutException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, SystemException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, RegularExpressionException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, LibraryLoadException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, LibraryAlreadyLoadedException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, NoThreadAvailableException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, PropertyNotSupportedException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, PoolOverflowException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, NoPermissionException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, OutOfMemoryException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, DataException, RuntimeException)

UTIL_DECLARE_EXCEPTION(Util_API, DataFormatException, DataException)
UTIL_DECLARE_EXCEPTION(Util_API, SyntaxException, DataException)
UTIL_DECLARE_EXCEPTION(Util_API, CircularReferenceException, DataException)
UTIL_DECLARE_EXCEPTION(Util_API, PathSyntaxException, SyntaxException)
UTIL_DECLARE_EXCEPTION(Util_API, IOException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, ProtocolException, IOException)
UTIL_DECLARE_EXCEPTION(Util_API, FileException, IOException)
UTIL_DECLARE_EXCEPTION(Util_API, FileExistsException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, FileNotFoundException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, PathNotFoundException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, FileReadOnlyException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, FileAccessDeniedException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, CreateFileException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, OpenFileException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, WriteFileException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, ReadFileException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, DirectoryNotEmptyException, FileException)
UTIL_DECLARE_EXCEPTION(Util_API, UnknownURISchemeException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, TooManyURIRedirectsException, RuntimeException)
UTIL_DECLARE_EXCEPTION(Util_API, URISyntaxException, SyntaxException)

UTIL_DECLARE_EXCEPTION(Util_API, ApplicationException, Exception)
UTIL_DECLARE_EXCEPTION(Util_API, BadCastException, RuntimeException)


} // namespace Util


#endif // __EXCEPTION_H_1652__
