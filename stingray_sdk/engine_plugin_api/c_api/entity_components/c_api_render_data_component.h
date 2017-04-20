#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct EntityWithInstanceId
{
	EntityRef entity;
	InstanceId instance_id;
};

struct RenderDataComponentCApi
{
	unsigned (*get_instances_with_tag)(RenderDataComponentPtr comp, unsigned tag, EntityWithInstanceId* out_buffer, unsigned buffer_size);
	void (*add_instance_to_tags)(RenderDataComponentPtr comp, EntityRef entity_ref, InstanceId instanceId, const unsigned* tags, const unsigned num_tags);
};

#ifdef __cplusplus
}
#endif
