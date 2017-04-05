#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct DebugNameComponentCApi
{
	void (*set_debug_name)(DebugNameComponentPtr comp, EntityRef entity, const char *debug_name);
};

#ifdef __cplusplus
}
#endif
