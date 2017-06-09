#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct UnitComponentCApi
{
	/* Gets the unit attached to the unit component. */
	CApiUnitRef (*unit)(UnitComponentPtr component, Instance instance);
};

#ifdef __cplusplus
}
#endif
