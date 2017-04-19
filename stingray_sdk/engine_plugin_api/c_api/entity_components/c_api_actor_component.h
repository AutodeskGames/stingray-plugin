#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ActorComponentCApi
{
	Instance (*create_capsule)(ActorComponentPtr comp, EntityRef e_ref, unsigned instance_id, ConstMatrix4x4Ptr pose_pointer, float radius, float height,
		unsigned actor_template_id32, unsigned shape_template_id32, unsigned material_template_id32);
	Instance (*create_plane)(ActorComponentPtr comp, EntityRef e_ref, unsigned instance_id, ConstMatrix4x4Ptr pose_pointer, ConstVector3Ptr normal_pointer,
		unsigned actor_template_id32, unsigned shape_template_id32, unsigned material_template_id32);
	Instance (*create_box)(ActorComponentPtr comp, EntityRef e_ref, unsigned instance_id, ConstMatrix4x4Ptr pose_pointer, ConstVector3Ptr half_extents_pointer,
		unsigned actor_template_id32, unsigned shape_template_id32, unsigned material_template_id32);
	Instance (*create_sphere)(ActorComponentPtr comp, EntityRef e_ref, unsigned instance_id, ConstMatrix4x4Ptr pose_pointer, float radius,
		unsigned actor_template_id32, unsigned shape_template_id32, unsigned material_template_id32);
	Instance (*create_mesh)(ActorComponentPtr comp, EntityRef e_ref, unsigned instance_id, ConstMatrix4x4Ptr pose_pointer, void *physics_mesh,
		unsigned actor_template_id32, unsigned shape_template_id32, unsigned material_template_id32);
};

#ifdef __cplusplus
}
#endif
