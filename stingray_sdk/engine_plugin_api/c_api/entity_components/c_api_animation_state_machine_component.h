#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct AnimationStateMachineComponentCApi
{
	int (*has_event)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned event_name_id32);
	void (*trigger_event)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned event_name_id32, const char *optional_debug_event_name);
	unsigned (*find_variable)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned variable_name_id32);
	float (*get_variable)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned index);
	void (*set_variable)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned index, float value);
	void (*set_logging)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, int enabled);
	void (*set_constraint_target)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned index, ConstMatrix4x4Ptr pose);
	void (*set_constraint_target_position)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned index, ConstVector3Ptr pos);
	void (*set_constraint_target_rotation)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned index, ConstQuaternionPtr rot);
	ConstMatrix4x4Ptr (*get_constraint_target)(AnimationStateMachineComponentPtr comp, EntityRef e_ref, unsigned index);
};

#ifdef __cplusplus
}
#endif
