#pragma once

// Platform names
#define PLATFORM_NAME_WIN32		"win32"
#define PLATFORM_NAME_XB1		"xb1"
#define PLATFORM_NAME_ANDROID	"android"
#define PLATFORM_NAME_MACOSX	"macosx"
#define PLATFORM_NAME_IOS		"ios"
#define PLATFORM_NAME_PS4		"ps4"
#define PLATFORM_NAME_WEB		"web"
#define PLATFORM_NAME_LINUX		"linux"
#define PLATFORM_NAME_UWP		"uwp"

#if defined(XBOXONE)
	#include <intrin.h>
	#include <stdint.h>
	__forceinline uint64_t rdtsc(void) { return __rdtsc(); }
#endif

#if defined(IOS)
	#include <errno.h>
#endif

#if defined(WINDOWSPC) || defined(UWP) || defined(XBOXONE)
	#define __ALIGN(x) __declspec(align(x))
	#define __THREAD __declspec(thread)
#elif defined(IOS) || defined(ANDROID) || defined(WEB) || defined(LINUXPC) || defined(MACOSX)
	#define __forceinline __attribute__((__always_inline__)) inline
	#define __ALIGN(x) __attribute__((aligned(x)))
	#define __THREAD
#elif defined(PS4)
	#define __forceinline __inline__ __attribute__((always_inline))
	#define __ALIGN(x) __attribute__((aligned(x)))
	#define __THREAD __thread
#endif

#if defined(ANDROID)
	#define PLUGIN_DLLEXPORT
#elif defined(IOS)
	#define PLUGIN_DLLEXPORT __attribute__((visibility("default")))
#else
	#define PLUGIN_DLLEXPORT __declspec(dllexport)
#endif
