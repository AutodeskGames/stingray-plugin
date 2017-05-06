#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MeshComponentCApi
{
	void (*set_mesh_resource)(MeshComponentPtr comp, Instance instance, uint64_t scene_resource_id64,
		const char *optional_debug_scene_resource_name, unsigned mesh_name_id32, const char *optional_debug_mesh_name);
	void (*set_mesh_object)(MeshComponentPtr comp, Instance instance, MeshPtr mesh_object);
	void (*set_material)(MeshComponentPtr comp, Instance instance, unsigned key_id32, uint64_t material_resource_id64,
		const char *optional_debug_material_resource_name, unsigned material_id32, const char *optional_debug_material_name);
};

#ifdef __cplusplus
}
#endif
