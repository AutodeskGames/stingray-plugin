#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MoverCApi
{
	UnitRef (*unit) (MoverPtr mover);
	void (*set_position) (MoverPtr mover, ConstVector3Ptr position);
	CApiVector3 (*position) (MoverPtr mover);

	void (*move) (MoverPtr mover, ConstVector3Ptr offset, float delta_time);
	struct MoverSeparateResult (*separate) (MoverPtr mover, float permitted_move_threshold);
	struct MoverFitsAtResult (*fits_at) (MoverPtr mover, ConstVector3Ptr, float permitted_move_threshold);

	int (*collides_down) (MoverPtr mover);
	int (*collides_up) (MoverPtr mover);
	int (*collides_sides) (MoverPtr mover);
	ActorPtr (*actor_colliding_down) (MoverPtr mover);

	unsigned (*standing_frames) (MoverPtr mover);
	unsigned (*flying_frames) (MoverPtr mover);

	void (*set_collision_filter) (MoverPtr mover, unsigned collision_filter_id32);
	float (*max_slope_angle) (MoverPtr mover);
	void (*set_max_slope_angle) (MoverPtr mover, float value);
	float (*radius) (MoverPtr mover);
};

#ifdef __cplusplus
}
#endif
