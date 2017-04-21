#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MaterialCApi
{
	void (*set_scalar)(MaterialPtr material_pointer, unsigned variable_name_id32, float value);
	void (*set_vector2)(MaterialPtr material_pointer, unsigned variable_name_id32, ConstVector2Ptr value);
	void (*set_vector3)(MaterialPtr material_pointer, unsigned variable_name_id32, ConstVector3Ptr value);
	void (*set_vector4)(MaterialPtr material_pointer, unsigned variable_name_id32, ConstVector4Ptr value);

	unsigned (*material_id)(ConstMaterialPtr material_pointer);
	void (*set_shader_pass_flag)(MaterialPtr material_pointer, unsigned flag_name_id32, int enabled);
	void (*set_texture)(MaterialPtr material_pointer, unsigned slot_name_id32, uint64_t texture_resource_name_id64, const char *optional_debug_texture_resource_name);
	void (*set_resource)(MaterialPtr material_pointer, unsigned slot_name_id32, ConstRenderResourcePtr render_resource);
	void (*set_matrix4x4)(MaterialPtr material_pointer, unsigned variable_name_id32, ConstMatrix4x4Ptr value);
};

#ifdef __cplusplus
}
#endif
