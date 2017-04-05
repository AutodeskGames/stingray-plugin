#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct SceneGraphComponentCApi
{
	unsigned (*num_nodes)(SceneGraphComponentPtr comp, EntityRef e_ref);
	unsigned (*node_index)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_name_id32);
	unsigned (*parent)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index);

	void (*set_local_position)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index, ConstVector3Ptr new_pos);
	void (*set_local_rotation)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index, ConstQuaternionPtr new_rot);
	void (*set_local_scale)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index, ConstVector3Ptr new_scale);
	void (*set_local_pose)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index, ConstLocalTransformPtr new_pose);

	ConstVector3Ptr (*local_position)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index);
	CApiQuaternion (*local_rotation)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index);
	ConstVector3Ptr (*local_scale)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index);
	ConstLocalTransformPtr (*local_pose)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index);

	ConstVector3Ptr (*world_position)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index);
	CApiQuaternion (*world_rotation)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index);
	ConstMatrix4x4Ptr (*world_pose)(SceneGraphComponentPtr comp, EntityRef e_ref, unsigned node_index);
};

#ifdef __cplusplus
}
#endif
