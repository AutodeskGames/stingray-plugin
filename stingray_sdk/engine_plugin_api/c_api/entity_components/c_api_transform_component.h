#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct TransformComponentCApi
{
	// Fills the specified buffer with up to (buffer_size) number of children of the component.
	// Returns the total number of children the component has.
	unsigned (*children)(TransformComponentPtr comp, Instance the_parent, EntityRef *buffer, unsigned buffer_size);

	EntityRef (*parent)(TransformComponentPtr comp, Instance the_child);
	void (*unlink)(TransformComponentPtr comp, Instance the_child);
	void (*link)(TransformComponentPtr comp, Instance the_child, Instance the_parent, ConstLocalTransformPtr child_local_pose);
	void (*link_to_scene_graph)(TransformComponentPtr comp, Instance the_child, Instance the_parent, unsigned parent_node_index, ConstLocalTransformPtr child_local_pose);

	void (*set_local_position)(TransformComponentPtr comp, Instance instance, ConstVector3Ptr new_pos);
	void (*set_local_rotation)(TransformComponentPtr comp, Instance instance, ConstQuaternionPtr new_rot);
	void (*set_local_scale)(TransformComponentPtr comp, Instance instance, ConstVector3Ptr new_scale);
	void (*set_local_pose)(TransformComponentPtr comp, Instance instance, ConstLocalTransformPtr new_pose);

	ConstVector3Ptr (*local_position)(TransformComponentPtr comp, Instance instance);
	CApiQuaternion (*local_rotation)(TransformComponentPtr comp, Instance instance);
	ConstVector3Ptr (*local_scale)(TransformComponentPtr comp, Instance instance);
	ConstLocalTransformPtr (*local_pose)(TransformComponentPtr comp, Instance instance);

	ConstVector3Ptr (*world_position)(TransformComponentPtr comp, Instance instance);
	CApiQuaternion (*world_rotation)(TransformComponentPtr comp, Instance instance);
	ConstMatrix4x4Ptr (*world_pose)(TransformComponentPtr comp, Instance instance);
};

#ifdef __cplusplus
}
#endif
