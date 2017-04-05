#pragma once

#include <assert.h>
#include "../engine_plugin_api/plugin_api.h"

#if defined(DEVELOPMENT)
	namespace stingray_plugin_foundation {
		inline struct ErrorApi *&error_api()
		{
			static struct ErrorApi *api = nullptr;
			return api;
		}
		inline void set_error_api(struct ErrorApi *api)
		{
			error_api() = api;
		}
	}

	#define XASSERT_BASE(test, test_msg, msg, ...) \
		do {if (!(test)) { \
				struct ErrorApi *api = stingray_plugin_foundation::error_api(); \
				if (api && api->report_assert_failure) \
					api->report_assert_failure(__LINE__, __FILE__, test_msg, api->eprintf(msg, ## __VA_ARGS__)); \
				else \
					assert(test); \
		}} while (0)
	#define XASSERT(test, msg, ...) do {XASSERT_BASE(test, #test, msg, ## __VA_ARGS__);} while(0)
	#define XENSURE(test) 			do {XASSERT_BASE(test, #test, "Assertion failed");} while(0)
	#define XERROR(msg, ...) 		do {XASSERT_BASE(false, nullptr, msg, ## __VA_ARGS__);} while(0)
#else
	#define XASSERT(test, msg, ...)		((void)0)
	#define XENSURE(test)				((void)0)
	#define XERROR(msg, ...) 			((void)0)

	namespace stingray_plugin_foundation {
		inline void set_error_api(struct ErrorApi *api) {}
	}
#endif
