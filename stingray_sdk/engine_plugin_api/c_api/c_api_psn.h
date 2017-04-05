#pragma once

#if defined(PS4)
	#include <platforms/ps4/sdk/engine_plugin_api/c_api/c_api_psn.h>
#else
	#ifdef __cplusplus
		extern "C" {
	#endif
			struct PsnCApi;
	#ifdef __cplusplus
		}
	#endif
#endif
