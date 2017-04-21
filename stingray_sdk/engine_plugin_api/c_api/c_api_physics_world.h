#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct PhysicsWorldCApi
{
	/*
		The raycast, sweep and overlap function calls will return the total number of hits made as an unsigned.
		Up to num_elements results will be stored in the pre-allocated out_buffer you provide.
	*/

	unsigned	(*raycast) (struct CollisionHit* out_buffer, unsigned num_elements, PhysicsWorldPtr, ConstVector3Ptr from, ConstVector3Ptr direction,
						enum RaycastType, enum ActorTemplate, unsigned collision_filter_id32, float length);

	unsigned	(*cast) (RaycastId, struct CollisionHit* out_buffer, unsigned num_elements, ConstVector3Ptr from, ConstVector3Ptr direction, float length);

	/*	Returns a unique id that can be used with the cast() function as many times as needed.
		The caller is responsible for deallocating this by calling destroy_raycast(). */
	RaycastId	(*make_raycast) (PhysicsWorldPtr, enum RaycastType, enum ActorTemplate, unsigned collision_filter_id32);
	void		(*destroy_raycast) (RaycastId);

	unsigned	(*overlap) (ActorPtr* out_buffer, unsigned num_elements, PhysicsWorldPtr, enum OverlapShape, ConstVector3Ptr optional_position, ConstQuaternionPtr optional_rotation,
							ConstMatrix4x4Ptr optional_pose, ConstVector3Ptr optional_size, enum ActorTemplate, unsigned collision_filter_id32);

	unsigned	(*linear_sphere_sweep) (struct CollisionHit* out_buffer, unsigned num_elements, PhysicsWorldPtr, ConstVector3Ptr from, ConstVector3Ptr to,
										float radius, enum ActorTemplate, unsigned collision_filter_id32, int report_initial_overlap);

	unsigned	(*linear_capsule_sweep) (struct CollisionHit* out_buffer, unsigned num_elements, PhysicsWorldPtr, ConstVector3Ptr from, ConstVector3Ptr to, ConstQuaternionPtr rotation,
										float radius, float half_height, enum ActorTemplate, unsigned collision_filter_id32, int report_initial_overlap);

	unsigned	(*linear_obb_sweep) (struct CollisionHit* out_buffer, unsigned num_elements, PhysicsWorldPtr, ConstVector3Ptr from, ConstVector3Ptr to, ConstVector3Ptr extents,
									ConstQuaternionPtr rotation, enum ActorTemplate, unsigned collision_filter_id32, int report_initial_overlap);
};

#ifdef __cplusplus
}
#endif
