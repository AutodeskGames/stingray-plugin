#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ScatterSystemCApi
{
	/*	Default values for make_brush parameters are:
		ScatterFadeMethod::SCATTER_FADE_POP
		fade_range: 5.0
		fade_from:	(POP) 0.f (SCALE) 0.f (SLIDE_Z) -2.f
		fade_to:	(POP) 0.f (SCALE) 1.f (SLIDE_Z) 0.f
		pool_size: UINT_MAX
		preheat_pool: false
		user_setting_density: true
	*/
	ScatterBrushId (*make_brush) (ScatterSystemPtr, uint64_t unit_id64, float spawn_distance, float unspawn_distance, enum ScatterFadeMethod,
									float fade_range, float fade_from, float fade_to, unsigned pool_size, int preheat_pool, int user_setting_density);

	void	(*destroy_brush) (ScatterSystemPtr, ScatterBrushId);
	void	(*destroy_all_brushes) (ScatterSystemPtr);

	ScatterUnitId (*spawn) (ScatterSystemPtr, ScatterBrushId, ConstVector3Ptr position, ConstQuaternionPtr optional_rotation);
	void	(*unspawn) (ScatterSystemPtr, ScatterUnitId);

	ScatterObserverId (*make_observer) (ScatterSystemPtr, ConstVector3Ptr position, ConstQuaternionPtr optional_rotation);
	void	(*destroy_observer) (ScatterSystemPtr, ScatterObserverId);
	void	(*move_observer) (ScatterSystemPtr, ScatterObserverId, ConstVector3Ptr position, ConstQuaternionPtr optional_rotation);
};

#ifdef __cplusplus
}
#endif
