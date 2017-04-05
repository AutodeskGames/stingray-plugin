#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Defines what should happen if a linked effect becomes orphaned. Should it
	be destroyed, stop spawning or be unlinked and continue to spawn. */
struct WorldCApi
{
	UnitRef	 (*spawn_unit) (WorldPtr world_pointer, uint64_t unit_name_id64, const char *optional_debug_unit_name, ConstMatrix4x4Ptr transform);
	void	 (*destroy_unit) (WorldPtr world_pointer, UnitRef unit_ref);
	unsigned (*num_units) (ConstWorldPtr world_pointer);

	UnitRef	(*unit_by_name) (WorldPtr world_pointer, uint64_t unit_name);
	UnitRef (*unit_by_id) (WorldPtr world_pointer, uint64_t unit_id);
	UnitRef (*unit_by_index) (WorldPtr world_pointer, unsigned index);
	unsigned (*num_units_by_resource) (WorldPtr world_pointer, uint64_t resource_name);
	unsigned (*units_by_resource)(WorldPtr world_pointer, uint64_t resource_name, unsigned max_unit_count, UnitRef* units);

	void	(*link_unit) (WorldPtr world_pointer, UnitRef child, unsigned child_node_index, UnitRef parent, unsigned parent_node_index);
	void	(*unlink_unit) (WorldPtr world_pointer, UnitRef child);
	void	(*update_unit) (WorldPtr world_pointer, UnitRef unit_ref);
	ParticleRef (*create_particles) (WorldPtr world_pointer, uint64_t name_id64, const char *optional_debug_name, ConstMatrix4x4Ptr transform);
	void	(*destroy_particles) (WorldPtr world_pointer, ParticleRef id);
	void	(*stop_spawning_particles) (WorldPtr world_pointer, ParticleRef id);
	int		(*are_particles_playing) (ConstWorldPtr world_pointer, ParticleRef id);
	void	(*set_particles_collision_filter) (ConstWorldPtr world_pointer, uint32_t collision_filter_name);

	void	(*move_particles) (WorldPtr world_pointer, ParticleRef id, ConstMatrix4x4Ptr transform);
	void	(*link_particles) (WorldPtr world_pointer, ParticleRef id, UnitRef unit_ref, unsigned unit_node_index, ConstMatrix4x4Ptr local_pose, enum WorldCApi_OrphanedParticlePolicy orphaned_policy);

	unsigned (*find_particles_variable) (ConstWorldPtr world_pointer, uint64_t name_id64, const char *optional_debug_name, unsigned variable_name_id32);
	void	 (*set_particles_variable) (WorldPtr world_pointer, ParticleRef id, unsigned variable, ConstVector3Ptr value);

	LevelPtr (*load_level) (WorldPtr world_pointer, uint64_t level_name_id64, const char *optional_debug_level_name, ConstMatrix4x4Ptr transform, uint64_t optional_level_id);
	void	 (*destroy_level) (WorldPtr world_pointer, LevelPtr level_pointer);
	unsigned (*num_levels) (ConstWorldPtr world_pointer);
	LevelPtr (*level) (WorldPtr world_pointer, unsigned index);

	void	(*update) (WorldPtr world_pointer, float dt);
	void	(*update_animations) (WorldPtr world_pointer, float dt, CApiCallbackFunction optional_callback, CallbackData32Ptr callback_data32);
	void	(*update_scene) (WorldPtr world_pointer, float dt);

	float	(*delta_time) (ConstWorldPtr world_pointer);
	float	(*time) (ConstWorldPtr world_pointer);

	StoryTellerPtr	 (*storyteller) (WorldPtr world_pointer);
	VectorFieldPtr	 (*vector_field) (WorldPtr world_pointer, unsigned vector_field_name_id32);
	ScatterSystemPtr (*scatter_system) (WorldPtr world_pointer);

	ShadingEnvironmentPtr (*create_shading_environment) (WorldPtr world_pointer, uint64_t name_id64, const char *optional_debug_name);
	ShadingEnvironmentPtr (*create_default_shading_environment) (WorldPtr world_pointer);
	void (*destroy_shading_environment) (WorldPtr world_pointer, ShadingEnvironmentPtr shading_environment_pointer);
	void (*set_shading_environment) (WorldPtr world_pointer, ShadingEnvironmentPtr shading_environment, uint64_t name_id64, const char *optional_debug_name);

	LineObjectPtr		(*create_line_object) (WorldPtr world_pointer, int disable_depth_test);
	void				(*destroy_line_object) (WorldPtr world_pointer, LineObjectPtr line_object_pointer);
	void				(*clear_permanent_lines) (WorldPtr world_pointer);

	GuiPtr	(*create_screen_gui) (WorldPtr world_pointer, ConstVector2Ptr optional_position, ConstVector2Ptr optional_scale, int immediate, int dock_right, int dock_top);
	GuiPtr	(*create_world_gui) (WorldPtr world_pointer, ConstMatrix4x4Ptr transform, float width, float height, int shadow_caster, int immediate);
	void	(*destroy_gui) (WorldPtr world_pointer, GuiPtr gui_pointer);
	GuiPtr	(*get_gui_by_id) (WorldPtr world_pointer, unsigned gui_id);

	PhysicsWorldPtr	(*physics_world) (WorldPtr world_pointer);

	VideoPlayerPtr	(*create_video_player) (WorldPtr world_pointer, uint64_t resource_id64, int loop);
	void			(*destroy_video_player) (WorldPtr world_pointer, VideoPlayerPtr video_player);

	ConstMatrix4x4Ptr	(*debug_camera_pose) (WorldPtr world_pointer);

	/* Begin Development functions */
	void	(*set_flow_enabled) (WorldPtr world_pointer, int enable);
	void	(*set_editor_flow_enabled) (WorldPtr world_pointer, int enable);

	unsigned	(*num_particles)(WorldPtr world_pointer, unsigned* optional_effect_id, unsigned* optional_cloud_index);
	void		(*advance_particles_time)(WorldPtr world_pointer, unsigned id, float time);

	void		(*set_frustum_inspector_camera) (WorldPtr world_pointer, CameraPtr camera_pointer);

	ReplayPtr	(*replay)(WorldPtr world_pointer);
	void		(*start_playback)(ReplayPtr replay_ptr);
	void		(*stop_playback)(ReplayPtr replay_ptr);
	int			(*is_playing_back)(ReplayPtr replay_ptr);
	int			(*num_frames)(ReplayPtr replay_ptr);
	int			(*frame)(ReplayPtr replay_ptr);
	void		(*set_frame)(ReplayPtr replay_ptr, unsigned frame_index);
	void		(*record_debug_line)(ReplayPtr replay_ptr, ConstVector4Ptr color, ConstVector2Ptr p1, ConstVector2Ptr p2);
	void		(*record_screen_debug_text)(ReplayPtr replay_ptr, ConstVector4Ptr color, ConstVector2Ptr screen_position, const char* text);
	void		(*record_world_debug_text)(ReplayPtr replay_ptr, ConstVector4Ptr color, ConstVector3Ptr world_position, const char* text);
	void		(*set_unit_record_mode)(ReplayPtr replay_ptr, UnitRef unit, enum ReplayRecordMode replay_record_mode);
	/* End Development functions */
};

#ifdef __cplusplus
}
#endif
