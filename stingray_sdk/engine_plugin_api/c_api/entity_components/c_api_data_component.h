#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct DataComponentCApi
{
	unsigned (*instance_ids_with_tag)(DataComponentPtr comp, EntityRef e_ref, unsigned tag_id32, InstanceId *buffer, unsigned buffer_size);
};

#ifdef __cplusplus
}
#endif
