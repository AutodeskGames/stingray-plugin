#pragma once

#include "../engine_plugin_api/plugin_api_types.h"

namespace stingray_plugin_foundation {

typedef unsigned short half;

typedef CApiVector2 Vector2;
typedef CApiVector3 Vector3;
typedef CApiVector4 Vector4;
typedef CApiMatrix4x4 Matrix4x4;
typedef CApiQuaternion Quaternion;
typedef CApiMatrix3x3 Matrix3x3;
typedef CApiLocalTransform LocalTransform;

struct Matrix4x4Elements {
	enum Enum {
		xx, xy, xz, xw,
		yx, yy, yz, yw,
		zx, zy, zz, zw,
		tx, ty, tz, tw
	};
	int dummy;
};

struct WorldConfig : public CApiWorldConfig {
	WorldConfig()
	{
		disable_physics = false;
		disable_sound = false;
		disable_rendering = false;
		enable_replay = false;
		physics_world_settings.apex_cloth = false;
		physics_world_settings.apex_lod_resource_budget = 0.f;
		physics_world_settings.step_frequency = 0;
		physics_world_settings.max_substeps = 0;
		physics_world_settings.async_timestep = false;
		physics_world_settings.swept_integration = false;
		decals = 0;
	}
};

}
