#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct LevelCApi
{
	WorldPtr	(*world) (LevelPtr level_pointer);
	void		(*spawn_background) (LevelPtr level_pointer);

	UnitRef		(*unit_by_index) (LevelPtr level_pointer, unsigned index);
	unsigned	(*unit_index) (LevelPtr level_pointer, UnitRef unit_ref);
	unsigned	(*num_units) (LevelPtr level_pointer);

	unsigned	(*num_nested_levels) (LevelPtr level_pointer);
	LevelPtr	(*nested_level) (LevelPtr level_pointer, unsigned index);

	unsigned	(*num_entities) (LevelPtr level_pointer);
	EntityRef	(*entity) (LevelPtr level_pointer, unsigned index);

	CApiVector3	(*random_point_inside_volume) (ConstLevelPtr level_pointer, unsigned volume_name_id32);
	CApiVector3	(*next_random_point_inside_volume) (ConstLevelPtr level_pointer, unsigned volume_name_id32, int, int*);
	int			(*is_point_inside_volume) (ConstLevelPtr level_pointer, unsigned volume_name_id32, ConstVector3Ptr vector3_pointer);
	int			(*has_volume) (ConstLevelPtr level_pointer, unsigned volume_name_id32);

	void		(*flow_event) (LevelPtr level_pointer, unsigned event_name_id32);
	unsigned	(*flow_variable_type) (LevelPtr level_pointer, unsigned variable_name_id32);
	void*		(*flow_variable) (LevelPtr level_pointer, unsigned variable_name_id32);
	void		(*set_flow_variable) (LevelPtr level_pointer, unsigned variable_name_id32, void* value);

	void		(*trigger_event) (LevelPtr level_pointer, unsigned event_name_id32);
	void		(*trigger_level_loaded) (LevelPtr level_pointer);
	void		(*trigger_level_shutdown) (LevelPtr level_pointer);
	void		(*trigger_level_update) (LevelPtr level_pointer);

	ConstMatrix4x4Ptr (*pose) (LevelPtr level_pointer);

	ConstNavigationMeshPtr (*navigation_mesh)(ConstLevelPtr level_pointer);

	struct Vector3ArrayWrapper (*spline)(LevelPtr level_pointer, unsigned spline_name_id32);
	unsigned			(*num_splines)(LevelPtr level_pointer);
	struct Vector3ArrayWrapper (*spline_by_index)(LevelPtr level_pointer, unsigned index);

	/* Begin development only functions */
	void				(*set_pose)(LevelPtr level_pointer, ConstMatrix4x4Ptr pose);
	void				(*set_visibility)(LevelPtr level_pointer, int visible);

	struct OOBBWrapper	(*box)(LevelPtr level_pointer);

	unsigned			(*num_internal_units)(LevelPtr level_pointer);
	void				(*internal_units)(LevelPtr level_pointer, UnitRef* internal_units);
	/* End development only functions */
};

#ifdef __cplusplus
}
#endif
