#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MeshComponentCApi
{
	void (*set_mesh_resource)(MeshComponentPtr comp, Instance instance, uint64_t scene_resource_id64,
		const char *optional_debug_scene_resource_name, unsigned mesh_name_id32, const char *optional_debug_mesh_name);

	/* Fetch a mesh pointer using its instance */
	MeshPtr (*mesh)(MeshComponentPtr comp, Instance instance);

	void(*set_mesh_object)(MeshComponentPtr comp, Instance instance, MeshPtr mesh_object, unsigned node_name_id32);

	void (*set_material)(MeshComponentPtr comp, Instance instance, unsigned key_id32, uint64_t material_resource_id64,
		const char *optional_debug_material_resource_name, unsigned material_id32, const char *optional_debug_material_name);

	/* Sets min & max bounds in mesh local coordinates to be used for culling. */
	void (*set_bounding_box)(MeshPtr mesh, float min[3], float max[3]);

	/* Sets batch/drawcall information of the mesh */
	void (*set_batch_info)(MeshPtr mesh, void *batch_infos, uint32_t n_info);

	/* Assigns an array of materials to the mesh. material_resources is an array of material
	resources retrieved using ResourceManagerApi::get() */
	void (*set_materials)(MeshPtr mesh, WorldPtr world_ptr, void **materials, uint32_t n_materials);

	/* Sets visibility of the mesh for a specific MO_VisibilityContext */
	void (*set_visibility)(MeshPtr mesh, uint32_t visibility_context, uint8_t visibility_bool);

	/* Adds resources such as vertex buffers, index buffers and vertex declarations created through
	the RenderBufferApi or piped down from Lua. */
	void (*add_resource)(MeshPtr mesh, void *resource);
};

#ifdef __cplusplus
}
#endif
