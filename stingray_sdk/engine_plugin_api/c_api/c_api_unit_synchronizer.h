#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct UnitSynchronizerCApi
{
	void (*set_world) (UnitSynchronizerPtr unit_synchronizer_pointer, WorldPtr world_pointer);
	UnitRef (*spawn_unit)(UnitSynchronizerPtr unit_synchronizer_pointer, unsigned type_id32, uint64_t unit_name_id64, ConstMatrix4x4Ptr transform, const char *optional_debug_unit_name);
	void (*destroy_unit)(UnitSynchronizerPtr unit_synchronizer_pointer, UnitRef unit_ref);

	UnitRef (*game_object_id_to_unit)(UnitSynchronizerPtr unit_synchronizer_pointer, GameObjectId id);
	GameObjectId (*unit_to_game_object_id)(UnitSynchronizerPtr unit_synchronizer_pointer, UnitRef unit_ref);
};

#ifdef __cplusplus
}
#endif
