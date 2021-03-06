//
// port from poco-1.8.1
//


#include "util/debugger.h"
#include <sstream>
#include <cstdlib>
#include <cstdio>
#if defined(PLATFORM_OS_FAMILY_WINDOWS)
	#include "util/unWindows.h"
#elif defined(PLATFORM_OS_FAMILY_UNIX)
	#include <unistd.h>
	#include <signal.h>
#endif

// NOTE: In this module, we use the C library functions (fputs) for,
// output since, at the time we're called, the C++ iostream objects std::cout, etc.
// might not have been initialized yet.


namespace Util {


bool Debugger::isAvailable()
{
#if defined(_DEBUG)
	#if defined(PLATFORM_OS_FAMILY_WINDOWS)
		return IsDebuggerPresent() ? true : false;
	#elif defined(PLATFORM_OS_FAMILY_UNIX)
		return std::getenv("UTIL_ENABLE_DEBUGGER") ? true : false;
	#endif
#else
	return false;
#endif
}


void Debugger::message(const std::string& msg)
{
#if defined(_DEBUG)
	std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
	std::fputs(msg.c_str(), stderr);
	std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
	#if defined(PLATFORM_OS_FAMILY_WINDOWS)
	if (isAvailable())
	{
		#if defined(UTIL_WIN32_UTF8) && !defined(UTIL_NO_WSTRING)
		std::wstring umsg;
		UnicodeConverter::toUTF16(msg, umsg);
		umsg += '\n';
		OutputDebugStringW(umsg.c_str());
		#else
		OutputDebugStringA(msg.c_str());
		OutputDebugStringA("\n");
		#endif
	}
	#endif
#endif
}


void Debugger::message(const std::string& msg, const char* file, int line)
{
#if defined(_DEBUG)
	std::ostringstream str;
	str << msg << " [in file \"" << file << "\", line " << line << "]";
	message(str.str());
#endif
}


void Debugger::enter()
{
#if defined(_DEBUG)
	#if defined(PLATFORM_OS_FAMILY_WINDOWS)
	if (isAvailable())
	{
		DebugBreak();
	}
	#elif defined(PLATFORM_OS_FAMILY_UNIX)
	if (isAvailable())
	{
		kill(getpid(), SIGINT);
	}
	#endif
#endif
}


void Debugger::enter(const std::string& msg)
{
#if defined(_DEBUG)
	message(msg);
	enter();
#endif
}


void Debugger::enter(const std::string& msg, const char* file, int line)
{
#if defined(_DEBUG)
	message(msg, file, line);
	enter();
#endif
}


void Debugger::enter(const char* file, int line)
{
#if defined(_DEBUG)
	message("BREAK", file, line);
	enter();
#endif
}


} // namespace Util
