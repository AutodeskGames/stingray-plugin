#pragma once

namespace plugin_c_api {namespace api_assert_global {
	extern void crash_jump(int line, const char *file, const char *assert, const char *msg);
}}

#if defined(DEVELOPMENT)
	#define API_ASSERT(test, msg, ...) if (!(test)) { plugin_c_api::api_assert_global::crash_jump(__LINE__, __FILE__, #test, stingray::eprintf(msg, ## __VA_ARGS__)); }
#else
	#define API_ASSERT(test, msg, ...) ((void)0)
#endif
