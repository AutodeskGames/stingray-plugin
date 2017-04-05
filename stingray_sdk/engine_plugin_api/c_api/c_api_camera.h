#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct CameraCApi
{
	ConstVector3Ptr (*local_position)(ConstCameraPtr camera_pointer);
	CApiQuaternion (*local_rotation)(ConstCameraPtr camera_pointer);
	ConstVector3Ptr (*local_scale)(ConstCameraPtr camera_pointer);
	ConstLocalTransformPtr (*local_pose)(ConstCameraPtr camera_pointer);

	void (*set_local_position)(CameraPtr camera_pointer, UnitRef unit_ref, ConstVector3Ptr position_pointer);
	void (*set_local_rotation)(CameraPtr camera_pointer, UnitRef unit_ref, ConstQuaternionPtr quaternion_pointer);
	void (*set_local_scale)(CameraPtr camera_pointer, UnitRef unit_ref, ConstVector3Ptr scale_pointer);
	void (*set_local_pose)(CameraPtr camera_pointer, UnitRef unit_ref, ConstLocalTransformPtr local_transform_pointer);

	ConstVector3Ptr (*world_position)(ConstCameraPtr camera_pointer);
	ConstMatrix4x4Ptr (*world_pose)(ConstCameraPtr camera_pointer);
	// Performance-warning; Fetches the world_pose, extracts a Matrix3x3 from it and returns a copy on the stack.
	CApiQuaternion (*world_rotation)(ConstCameraPtr camera_pointer);

	float (*near_range)(ConstCameraPtr camera_pointer);
	float (*far_range)(ConstCameraPtr camera_pointer);
	void (*set_near_range)(CameraPtr camera_pointer, float near_range);
	void (*set_far_range)(CameraPtr camera_pointer, float far_range);

	float (*vertical_fov)(ConstCameraPtr camera_pointer, unsigned index);
	void (*set_vertical_fov)(CameraPtr camera_pointer, float fov, unsigned index);

	enum CameraProjectionType (*projection_type)(ConstCameraPtr camera_pointer);
	void (*set_projection_type)(CameraPtr camera_pointer, enum CameraProjectionType camera_projection_type);
	void (*set_orthographic_view)(CameraPtr camera_pointer, float min_x, float max_x, float min_z, float max_z, unsigned index);
	void (*set_post_projection_transform)(CameraPtr camera_pointer, ConstMatrix4x4Ptr transform);


	void (*set_frustum)(CameraPtr camera_pointer, float left, float right, float bottom, float top, unsigned index);
	void (*set_frustum_half_angles)(CameraPtr camera_pointer, float left_tan, float right_tan, float bottom_tan, float top_tan, unsigned index);
	float (*inside_frustum)(ConstCameraPtr camera_pointer, ConstVector3Ptr point, ConstWindowPtr optional_window);
	CApiMatrix4x4 (*projection)(ConstCameraPtr camera_pointer, float aspect_ratio);

	unsigned (*node)(ConstCameraPtr camera_pointer);

	enum CameraMode (*mode)(ConstCameraPtr camera_pointer);
	void (*set_mode)(CameraPtr camera_pointer, enum CameraMode mode);

	void (*set_local)(CameraPtr camera_pointer, ConstMatrix4x4Ptr m, unsigned index);

	CApiVector3 (*screen_to_world)(CameraPtr camera_pointer, ConstVector3Ptr point, float depth, unsigned screen_width, unsigned screen_height);
};

#ifdef __cplusplus
}
#endif

