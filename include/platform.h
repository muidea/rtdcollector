//
// port from poco-1.8.1
//


#ifndef __PLATFORM_H_1438__
#define __PLATFORM_H_1438__


//
// Platform Identification
//
#define PLATFORM_OS_LINUX         0x0005
#define PLATFORM_OS_CYGWIN        0x000d
#define PLATFORM_OS_WINDOWS_NT    0x1001


#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__) || defined(EMSCRIPTEN)
	#define PLATFORM_OS_FAMILY_UNIX 1
	#define PLATFORM_OS PLATFORM_OS_LINUX
#elif defined(__CYGWIN__)
	#define PLATFORM_OS_FAMILY_UNIX 1
	#define PLATFORM_OS PLATFORM_OS_CYGWIN
#elif defined(_WIN32) || defined(_WIN64)
	#define PLATFORM_OS_FAMILY_WINDOWS 1
	#define PLATFORM_OS PLATFORM_OS_WINDOWS_NT
#endif


#if !defined(PLATFORM_OS)
	#error "Unknown Platform."
#endif


//
// Hardware Architecture and Byte Order
//
#define PLATFORM_ARCH_IA32    0x02
#define PLATFORM_ARCH_IA64    0x03
#define PLATFORM_ARCH_AMD64   0x09
#define PLATFORM_ARCH_AARCH64 0x0f
#define PLATFORM_ARCH_ARM64   0x0f // same as PLATFORM_ARCH_AARCH64


#if defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86) || defined(EMSCRIPTEN)
	#define PLATFORM_ARCH PLATFORM_ARCH_IA32
	#define PLATFORM_ARCH_LITTLE_ENDIAN 1
#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
	#define PLATFORM_ARCH PLATFORM_ARCH_IA64
	#define PLATFORM_ARCH_LITTLE_ENDIAN 1
#elif defined(__x86_64__) || defined(_M_X64)
	#define PLATFORM_ARCH PLATFORM_ARCH_AMD64
	#define PLATFORM_ARCH_LITTLE_ENDIAN 1
#endif


#if defined(_MSC_VER)
	#define PLATFORM_COMPILER_MSVC
#elif defined(__clang__)
	#define PLATFORM_COMPILER_CLANG
#elif defined (__GNUC__)
	#define PLATFORM_COMPILER_GCC
#elif defined (__MINGW32__) || defined (__MINGW64__)
	#define PLATFORM_COMPILER_MINGW
#endif


#ifdef __GNUC__
#define PLATFORM_UNUSED __attribute__((unused))
#else
#define PLATFORM_UNUSED
#endif // __GNUC__


#if !defined(PLATFORM_ARCH)
	#error "Unknown Hardware Architecture."
#endif


#if defined(PLATFORM_OS_FAMILY_WINDOWS)
	#define PLATFORM_DEFAULT_NEWLINE_CHARS "\r\n"
#else
	#define PLATFORM_DEFAULT_NEWLINE_CHARS "\n"
#endif


#endif // __PLATFORM_H_1438__
