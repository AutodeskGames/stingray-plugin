#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MoverCApi
{
	UnitRef	(*unit) (MoverPtr);
	void	(*set_position) (MoverPtr, ConstVector3Ptr);
	CApiVector3 (*position) (MoverPtr);

	void	(*move) (MoverPtr, ConstVector3Ptr offset, float delta_time);
	struct MoverSeparateResult	(*separate) (MoverPtr, float permitted_move_threshold);
	struct MoverFitsAtResult	(*fits_at) (MoverPtr, ConstVector3Ptr, float permitted_move_threshold);

	int		(*collides_down) (MoverPtr);
	int		(*collides_up) (MoverPtr);
	int		(*collides_sides) (MoverPtr);
	ActorPtr (*actor_colliding_down) (MoverPtr);

	unsigned (*standing_frames) (MoverPtr);
	unsigned (*flying_frames) (MoverPtr);

	void	(*set_collision_filter) (MoverPtr, unsigned collision_filter_id32);
	float	(*max_slope_angle) (MoverPtr);
	void	(*set_max_slope_angle) (MoverPtr, float);
	float	(*radius) (MoverPtr);
};

#ifdef __cplusplus
}
#endif
