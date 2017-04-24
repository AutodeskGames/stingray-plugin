#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct FlowComponentCApi
{
	/* Triggers an event on the Flow attached to the specified Flow component instance. */
	void (*trigger_flow_event)(FlowComponentPtr component, Instance instance, unsigned event_id32);

	/* Returns a pointer to an external flow variable and an identifier specifying its type. */
	char *(*external_variable)(FlowComponentPtr component, Instance instance, unsigned variable_id32, unsigned *flow_variable_type);
};

#ifdef __cplusplus
}
#endif
