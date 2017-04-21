#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MeshCApi
{
	unsigned (*num_materials) (ConstMeshPtr);
	unsigned (*find_material) (ConstMeshPtr, unsigned name_id32);
	MaterialPtr (*material) (MeshPtr, unsigned index);
	unsigned (*node) (ConstMeshPtr);

	void (*set_shader_pass_flag) (MeshPtr, unsigned name_id32, int enabled);
	struct BoundingVolumeWrapper (*bounding_volume) (MeshPtr);
	void (*set_explicit_sort_value) (MeshPtr, unsigned sort_value);

	ConstVector3Ptr		(*local_position) (ConstMeshPtr);
	struct CApiQuaternion (*local_rotation) (ConstMeshPtr);
	ConstVector3Ptr		(*local_scale) (ConstMeshPtr);
	ConstLocalTransformPtr  (*local_pose) (ConstMeshPtr);

	void (*set_local_position) (MeshPtr, UnitRef, ConstVector3Ptr);
	void (*set_local_rotation) (MeshPtr, UnitRef, ConstQuaternionPtr);
	void (*set_local_scale) (MeshPtr, UnitRef, ConstVector3Ptr);
	void (*set_local_pose) (MeshPtr, UnitRef, ConstLocalTransformPtr);

	ConstVector3Ptr		(*world_position) (ConstMeshPtr);
	ConstMatrix4x4Ptr	(*world_pose) (ConstMeshPtr);
	// Performance-warning; Fetches the world_pose, extracts a Matrix3x3 from it and returns a copy on the stack.
	struct CApiQuaternion (*world_rotation) (ConstMeshPtr);
};

#ifdef __cplusplus
}
#endif
