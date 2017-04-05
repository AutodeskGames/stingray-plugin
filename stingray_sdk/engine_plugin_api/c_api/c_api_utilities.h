#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct UtilitiesProfilerApi
{
	void (*start) (const char* name);
	void (*stop) ();
	void (*record_statistics_float) (const char* name, float);
	void (*record_statistics_vector3) (const char* name, ConstVector3Ptr);
};

struct UtilitiesCApi
{
	struct UtilitiesProfilerApi* Profiler;
};

#ifdef __cplusplus
}
#endif
