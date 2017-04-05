#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ActorCApi
{
	int (*is_collision_enabled) (ActorPtr actor);
	int (*is_scene_query_enabled) (ActorPtr actor);
	int (*is_gravity_enabled) (ActorPtr actor);

	void (*set_collision_enabled) (ActorPtr actor, int enabled);
	void (*set_scene_query_enabled) (ActorPtr actor, int enabled);
	void (*set_gravity_enabled) (ActorPtr actor, int enabled);

	int (*is_static) (ActorPtr actor);
	int (*is_dynamic) (ActorPtr actor);
	int (*is_physical) (ActorPtr actor);
	int (*is_kinematic) (ActorPtr actor);
	void (*set_kinematic) (ActorPtr actor, int enabled);

	float (*mass) (ActorPtr actor);
	float (*linear_damping) (ActorPtr actor);
	float (*angular_damping) (ActorPtr actor);
	void (*set_linear_damping) (ActorPtr actor, float value);
	void (*set_angular_damping) (ActorPtr actor, float value);
	CApiVector3 (*center_of_mass) (ActorPtr actor);

	CApiVector3 (*position) (ActorPtr actor);
	CApiQuaternion (*rotation) (ActorPtr actor);
	CApiMatrix4x4 (*pose) (ActorPtr actor);

	void (*teleport_position) (ActorPtr actor, ConstVector3Ptr position);
	void (*teleport_rotation) (ActorPtr actor, ConstQuaternionPtr rotation);
	void (*teleport_pose) (ActorPtr actor, ConstMatrix4x4Ptr pose);

	void (*set_velocity) (ActorPtr actor, ConstVector3Ptr velocity);
	void (*set_angular_velocity) (ActorPtr actor, ConstVector3Ptr velocity);

	CApiVector3 (*velocity) (ActorPtr actor);
	CApiVector3 (*angular_velocity) (ActorPtr actor);
	CApiVector3 (*point_velocity) (ActorPtr actor, ConstVector3Ptr point);

	void (*add_impulse) (ActorPtr actor, ConstVector3Ptr amount);
	void (*add_velocity) (ActorPtr actor, ConstVector3Ptr amount);
	void (*add_torque_impulse) (ActorPtr actor, ConstVector3Ptr amount);
	void (*add_angular_velocity) (ActorPtr actor, ConstVector3Ptr amount);

	void (*add_impulse_at) (ActorPtr actor, ConstVector3Ptr impulse, ConstVector3Ptr position);
	void (*add_velocity_at) (ActorPtr actor, ConstVector3Ptr velocity, ConstVector3Ptr position);

	void (*push) (ActorPtr actor, ConstVector3Ptr velocity, float mass);
	void (*push_at) (ActorPtr actor, ConstVector3Ptr velocity, float mass, ConstVector3Ptr position);

	int (*is_sleeping) (ActorPtr actor);
	void (*wake_up) (ActorPtr actor);
	void (*put_to_sleep) (ActorPtr actor);

	void (*debug_draw) (ActorPtr actor, LineObjectPtr line_object, ConstVector4Ptr optional_color, ConstMatrix4x4Ptr optional_camera_pose);

	UnitRef (*unit) (ActorPtr actor);
	unsigned (*node) (ActorPtr actor);
	void (*set_collision_filter) (ActorPtr actor, unsigned collision_filter_id32);
	unsigned (*initial_shape_template) (ActorPtr actor, unsigned shape_index);  // returns IdString32.id of the initial shape template name.
};

#ifdef __cplusplus
}
#endif
