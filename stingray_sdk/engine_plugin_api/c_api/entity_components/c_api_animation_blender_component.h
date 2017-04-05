#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct AnimationBlenderComponentCApi
{
	unsigned (*crossfade)(AnimationBlenderComponentPtr comp, EntityRef e_ref, uint64_t animation_name_id64,
	const char *optional_debug_animation_name, unsigned layer, float blend_time, int should_loop, enum AnimationBlendType anim_blend_type);
	void (*set_time)(AnimationBlenderComponentPtr comp, EntityRef e_ref, unsigned id, float time, int should_cap_to_range);
	void (*set_speed)(AnimationBlenderComponentPtr comp, EntityRef e_ref, unsigned id, float speed);
	int (*is_crossfading)(AnimationBlenderComponentPtr comp, EntityRef e_ref);
	void (*set_root_mode)(AnimationBlenderComponentPtr comp, EntityRef e_ref, enum AnimationBoneRootMode mode);
	void (*set_bone_mode) (AnimationBlenderComponentPtr comp, EntityRef e_ref, enum AnimationBoneRootMode mode);
	void (*set_bones_lod)(AnimationBlenderComponentPtr comp, EntityRef e_ref, unsigned lod_level);
	CApiMatrix4x4 (*delta_transform)(AnimationBlenderComponentPtr comp, EntityRef e_ref);
	enum AnimationBoneRootMode (*root_mode)(AnimationBlenderComponentPtr comp, EntityRef e_ref);
	enum AnimationBoneRootMode (*bone_mode)(AnimationBlenderComponentPtr comp, EntityRef e_ref);
};


#ifdef __cplusplus
}
#endif
