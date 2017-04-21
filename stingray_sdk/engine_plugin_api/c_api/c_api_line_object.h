#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct LineObjectCApi
{
	void	(*dispatch) (WorldPtr, LineObjectPtr);
	void	(*reset) (LineObjectPtr);

	void	(*add_line) (LineObjectPtr, ConstVector4Ptr color, ConstVector3Ptr from, ConstVector3Ptr to);
	void	(*add_cone) (LineObjectPtr, ConstVector4Ptr color, ConstVector3Ptr from, ConstVector3Ptr to, float radius, unsigned num_segments, unsigned num_bars);
	void	(*add_circle) (LineObjectPtr, ConstVector4Ptr color, ConstVector3Ptr center, float radius, ConstVector3Ptr normal, unsigned num_segments);
	void	(*add_sphere) (LineObjectPtr, ConstVector4Ptr color, ConstVector3Ptr center, float radius, unsigned num_segments, unsigned num_parts);
	void	(*add_half_sphere) (LineObjectPtr, ConstVector4Ptr color, ConstVector3Ptr center, float radius, ConstVector3Ptr normal, unsigned num_segments, unsigned num_parts);
	void	(*add_box) (LineObjectPtr, ConstVector4Ptr color, ConstMatrix4x4Ptr pose, float radius, ConstVector3Ptr half_extents);
	void	(*add_capsule) (LineObjectPtr, ConstVector4Ptr color, ConstVector3Ptr from, ConstVector3Ptr to, float radius, unsigned num_segments, unsigned num_circles, unsigned num_bars);
	void	(*add_axes) (LineObjectPtr, ConstMatrix4x4Ptr pose, float length);

	/*	Not available in Release builds.	If camera_direction is supplied, back-facing triangles will get culled.	*/
	void	(*add_unit_meshes) (LineObjectPtr, uint64_t unit_resource_name_id64, const char *optional_debug_unit_resource_name, ConstVector4Ptr color, ConstMatrix4x4Ptr pose, ConstVector3Ptr optional_camera_direction);
};

#ifdef __cplusplus
}
#endif
