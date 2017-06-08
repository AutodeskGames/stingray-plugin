#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct UnitCApi
{
	ConstVector3Ptr			(*local_position) (UnitRef, unsigned index);
	CApiQuaternion (*local_rotation) (UnitRef, unsigned index);
	ConstVector3Ptr			(*local_scale) (UnitRef, unsigned index);
	ConstLocalTransformPtr  (*local_pose) (UnitRef, unsigned index);

	void	(*set_local_position) (UnitRef, unsigned index, ConstVector3Ptr);
	void	(*set_local_rotation) (UnitRef, unsigned index, ConstQuaternionPtr);
	void	(*set_local_scale) (UnitRef, unsigned index, ConstVector3Ptr);
	void	(*set_local_pose) (UnitRef, unsigned index, ConstLocalTransformPtr);

	ConstVector3Ptr			(*world_position) (UnitRef, unsigned index);
	ConstMatrix4x4Ptr		(*world_pose) (UnitRef, unsigned index);
	// Performance-warning; Fetches the world_pose, extracts a Matrix3x3 from it and returns a copy on the stack.
	CApiQuaternion (*world_rotation) (UnitRef, unsigned index);

	void	(*teleport_local_position) (UnitRef, unsigned index, ConstVector3Ptr);
	void	(*teleport_local_rotation) (UnitRef, unsigned index, ConstQuaternionPtr);
	void	(*teleport_local_scale) (UnitRef, unsigned index, ConstVector3Ptr);
	void	(*teleport_local_pose) (UnitRef, unsigned index, ConstLocalTransformPtr);

	CApiVector3	(*delta_position) (UnitRef, unsigned index);
	CApiQuaternion (*delta_rotation) (UnitRef, unsigned index);
	struct CApiMatrix4x4 (*delta_pose) (UnitRef, unsigned index);

	ActorPtr	(*create_actor) (UnitRef, unsigned index, float inherit_velocity, const char* optional_debug_actor_name);
	void		(*destroy_actor) (UnitRef, unsigned index, const char* optional_debug_actor_name);
	unsigned	(*num_actors) (UnitRef);
	unsigned	(*find_actor) (UnitRef, unsigned actor_name_id32, const char* optional_debug_actor_name);
	ActorPtr	(*actor) (UnitRef, unsigned index, const char* optional_debug_actor_name);

	unsigned	(*num_movers) (UnitRef);
	unsigned	(*find_mover) (UnitRef, unsigned mover_name_id32);
	MoverPtr	(*set_mover) (UnitRef, unsigned index, const char *optional_debug_mover_name);
	void		(*set_mover_to_none) (UnitRef);
	MoverPtr	(*mover) (UnitRef);
	struct MoverFitsAtResult (*mover_fits_at) (UnitRef unit_ref, unsigned index, ConstVector3Ptr position, float permitted_move_threshold, const char *optional_debug_mover_name);

	void		(*trigger_flow_event) (UnitRef, unsigned event_name_id32);
	void*		(*flow_variable) (UnitRef unit_ref, unsigned variable_name_id32, unsigned *out_type);
	void		(*set_flow_variable) (UnitRef, unsigned variable_name_id32, void* value);
	void		(*trigger_unit_spawned)(UnitRef unit_ref);

	uint64_t		(*set_material) (UnitRef, unsigned slot_name_id32, uint64_t material_resource_name_id64, const char *optional_debug_material_resource_name, unsigned debug_suppress_slot_assignment_warning);
	uint64_t		(*set_material_to_none) (UnitRef, unsigned slot_name_id32);
	unsigned		(*query_material)(UnitRef unit_ref, ConstVector3Ptr start, ConstVector3Ptr end, unsigned context_count, unsigned context_id32s[], unsigned out_material[]);
	MaterialDataPtr	(*save_instance_material_data)(UnitRef unit_ref);
	void			(*restore_instance_material_data)(UnitRef unit_ref, MaterialDataPtr data);
	int				(*is_using_material_set)(UnitRef unit_ref);

	unsigned	(*num_meshes) (UnitRef);
	unsigned	(*find_mesh) (UnitRef, unsigned mesh_name_id32);
	MeshPtr		(*mesh) (UnitRef, unsigned index, const char *optional_debug_mesh_name);

	struct BoneNamesWrapper	(*bones) (UnitRef);
	CApiMatrix4x4	(*animation_wanted_root_pose) (UnitRef);
	void	(*animation_set_bones_lod) (UnitRef, unsigned);

	enum AnimationBoneRootMode (*animation_root_mode) (UnitRef);
	enum AnimationBoneRootMode (*animation_bone_mode) (UnitRef);

	void		(*set_animation_root_mode) (UnitRef, enum AnimationBoneRootMode);
	void		(*set_animation_bone_mode) (UnitRef, enum AnimationBoneRootMode);

	unsigned	(*animation_find_constraint_target) (UnitRef unit_ref, unsigned constraint_target_name_id32, const char *optional_debug_target_name);
	unsigned	(*animation_has_constraint_target)(UnitRef unit_ref, unsigned constraint_target_name_id32);
	ConstMatrix4x4Ptr (*animation_get_constraint_target) (UnitRef, unsigned index);
	void		(*animation_set_constraint_target_pose) (UnitRef, unsigned index, ConstMatrix4x4Ptr);
	void		(*animation_set_constraint_target_position) (UnitRef, unsigned index, ConstVector3Ptr);
	void		(*animation_set_constraint_target_rotation) (UnitRef, unsigned index, ConstQuaternionPtr);

	unsigned	(*crossfade_animation) (UnitRef, uint64_t animation_name_id64, const char *optional_debug_animation_name, unsigned layer, float blend_time, int should_loop, enum AnimationBlendType);
	unsigned	(*is_crossfading_animation) (UnitRef);
	void		(*crossfade_animation_set_time) (UnitRef, unsigned id, float time, int should_cap_to_range);
	void		(*crossfade_animation_set_speed) (UnitRef, unsigned id, float speed);

	void		(*disable_animation_state_machine) (UnitRef);
	void		(*enable_animation_state_machine) (UnitRef);
	void		(*set_animation_state_machine) (UnitRef, uint64_t machine_name_id64, const char *optional_debug_machine_name);
	int			(*has_animation_state_machine) (UnitRef);
	int         (*has_animation_blender) (UnitRef);
	int			(*has_animation_event) (UnitRef, unsigned event_name_id32);

	void		(*animation_trigger_event) (UnitRef unit_ref, unsigned event_name_id32, const char *optional_debug_event_name);
	void		(*animation_trigger_event_with_parameters) (UnitRef unit_ref, unsigned event_name_id32, const char *optional_debug_event_name, struct AnimationEventParameters *parameters);

	unsigned	(*animation_find_variable) (UnitRef, unsigned variable_name_id32, const char *optional_debug_variable_name);
	int			(*animation_has_variable)(UnitRef unit_ref, unsigned variable_name_id32);
	float		(*animation_get_variable) (UnitRef, unsigned index);
	void		(*animation_set_variable) (UnitRef, unsigned index, float value);

	void		(*animation_set_state) (UnitRef, struct AnimationStates*);
	struct AnimationStates (*animation_get_state) (UnitRef);

	void(*animation_set_seeds) (UnitRef, struct AnimationLayerSeeds*);
	struct AnimationLayerSeeds(*animation_get_seeds) (UnitRef);

	struct AnimationLayerInfo (*animation_layer_info) (UnitRef, unsigned index);
	void		(*set_animation_merge_options) (UnitRef, float max_start_time, float max_drift, float clock_fidelity);

	void		(*animation_set_moving)(UnitRef unit_ref, unsigned frames);
	int			(*animation_get_curve_value)(UnitRef unit_ref, unsigned object_id32, unsigned parameter_id32, unsigned int float_index, float *out_curve_value);
	void		(*set_animation_logging)(UnitRef unit_ref, int enable);

	void		(*play_simple_animation)(UnitRef unit_ref, float from, float to, float speed, int loop, unsigned optional_group, const char *optional_debug_group_name);
	void		(*stop_simple_animation)(UnitRef unit_ref, unsigned optional_group, const char *optional_debug_group_name);

	unsigned	(*num_terrains) (UnitRef);
	unsigned	(*find_terrain) (UnitRef, unsigned terrain_name_id32);
	TerrainPtr	(*terrain) (UnitRef, unsigned index, const char *optional_debug_terrain_name);
	void		(*terrain_update_height_field)(UnitRef unit_ref, void *data);

	JointPtr	(*create_joint) (UnitRef, unsigned joint_name_id32, const char *optional_debug_joint_name);
	void		(*destroy_joint) (UnitRef, unsigned joint_name_id32);
	JointPtr	(*create_custom_joint) (UnitRef, unsigned joint_name_id32, ActorPtr optional_actor_1, ActorPtr optional_actor_2, ConstVector3Ptr optional_anchor_1,
										ConstVector3Ptr optional_anchor_2, ConstVector3Ptr optional_global_anchor, ConstVector3Ptr optional_global_axis,
										const char *optional_debug_joint_name);

	// Length of key_id32_array depenends on the path for the property
	void		(*set_property) (UnitRef unit_ref, float value, unsigned key_id32_array[]);
	float		(*get_property) (UnitRef unit_ref, unsigned key_id32_array[]);

	unsigned	(*num_scene_graph_items) (UnitRef);
	unsigned	(*find_scene_graph_parent) (UnitRef, unsigned index);
	void		(*scene_graph_link) (UnitRef, unsigned index, unsigned parent_index);
	void		(*scene_graph_link_to_none) (UnitRef, unsigned index);
	void		(*copy_scene_graph_local_from) (UnitRef destination, UnitRef source);

	unsigned		(*num_lod_objects) (UnitRef);
	unsigned		(*find_lod_object) (UnitRef, unsigned lod_name_id32);
	LodObjectPtr	(*lod_object) (UnitRef, unsigned index, const char *optional_debug_lod_name);
	unsigned		(*num_steps_lod) (LodObjectPtr lod_obj_ptr);
	void			(*lod_step_range) (LodObjectPtr lod_obj_ptr, unsigned step_index, float out_range[2]);
	unsigned		(*num_mesh_lod_step) (LodObjectPtr lod_obj_ptr, unsigned step_index);
	const unsigned*	(*lod_step_meshes) (LodObjectPtr lod_obj_ptr, unsigned step_index);

	unsigned	(*num_lights) (UnitRef);
	unsigned	(*find_light) (UnitRef, unsigned light_name_id32);
	LightPtr	(*light) (UnitRef, unsigned index, const char *optional_debug_light_name);
	void		(*set_light_material)(UnitRef unit_ref, LightPtr light_pointer, uint64_t material_name);

	VehiclePtr	(*create_vehicle) (UnitRef);
	void		(*destroy_vehicle) (UnitRef);
	int			(*has_vehicle) (UnitRef);
	VehiclePtr	(*vehicle) (UnitRef);

	void		(*enable_physics) (UnitRef);
	void		(*disable_physics) (UnitRef);
	void		(*apply_initial_actor_velocities) (UnitRef, int should_wake_sleeping_actors);

	void		(*set_unit_visibility) (UnitRef, int enabled);
	void		(*set_mesh_visibility) (UnitRef unit_ref, unsigned index, unsigned visbility_context_id32, int enabled, const char *optional_debug_mesh_name, const char *optional_debug_visbility_context_name);
	void		(*set_cloth_visibility) (UnitRef unit_ref, unsigned index, unsigned state, unsigned visbility_context_id32, const char *optional_debug_cloth_name, const char *optional_debug_visbility_context_name);
	void		(*set_visibility_group) (UnitRef, unsigned group_name_id32, int enabled, const char *optional_debug_group_name);
	int			(*has_visibility_group) (UnitRef, unsigned group_name_id32);

	ClothPtr	(*create_cloth) (UnitRef unit_ref, unsigned index, const char *optional_debug_cloth_name);
	void		(*destroy_cloth) (UnitRef unit_ref, unsigned index, const char *optional_debug_cloth_name);
	unsigned	(*num_cloths) (UnitRef unit_ref);
	unsigned	(*find_cloth) (UnitRef unit_ref, unsigned cloth_name_id32);
	ClothPtr	(*cloth) (UnitRef unit_ref, unsigned index, const char *optional_debug_cloth_name);

	unsigned	(*num_cameras) (UnitRef);
	unsigned	(*find_camera) (UnitRef, unsigned camera_name_id32);
	CameraPtr	(*camera) (UnitRef, unsigned index, const char *optional_debug_camera_name);

	int			(*has_node) (UnitRef, unsigned node_name_id32);
	unsigned	(*node) (UnitRef, unsigned node_name_id32, const char *optional_debug_node_name);

	int				(*resource_has_node)(uint64_t unit_resource_id64, unsigned node_id32, const char *optional_debug_unit_resource_name);
	unsigned		(*resource_node)(uint64_t unit_resource_id64, unsigned node_id32, const char *optional_debug_unit_resource_name, const char *optional_debug_node_name);
	// Performance-warning; Fetches the local_pose, extracts a Matrix4x4 from it and returns a copy on the stack.
	CApiMatrix4x4	(*resource_local_pose)(uint64_t unit_resource_id64, unsigned node_index, const char *optional_debug_unit_resource_name);

	WorldPtr	(*world) (UnitRef);
	LevelPtr	(*level) (UnitRef);
	int			(*is_alive) (UnitRef);
	uint64_t	(*id_in_level) (UnitRef);
	int			(*is_of_resource_type) (UnitRef, uint64_t resource_name);
	const char *(*unit_name_s)(UnitRef unit_ref);

	struct OOBBWrapper	(*box) (UnitRef unit_ref, unsigned ignore_invisible_meshes);
	const char *		(*debug_name)(UnitRef unit_ref);
	void				(*name_hash)(UnitRef unit_ref, char out_name[8]);
	int					(*is_a)(UnitRef unit_ref, uint64_t resource_id64);
	void				(*set_id_in_level)(UnitRef unit_ref, uint64_t id);
	void				(*draw_tree)(UnitRef unit_ref);

	unsigned	(*mesh_raycast)(UnitRef unit_ref, ConstVector3Ptr from, ConstVector3Ptr dir, float threshold, int include_hidden_meshes,
					float *out_distance, CApiVector3 *out_normal_world);
	unsigned	(*mesh_pick_raycast)(UnitRef unit_ref, ConstVector3Ptr from, ConstVector3Ptr dir, float threshold, int include_hidden_meshes,
					float *out_distance, CApiVector3 *out_normal_world, unsigned *out_best_mesh_index, unsigned *out_best_triangle_index);
	unsigned	(*mesh_closest_point_raycast)(UnitRef unit_ref, ConstVector3Ptr from, ConstVector3Ptr dir, float ray_length,
					CApiVector3 *out_best_point_world, float *out_best_point_distance_along_ray, float *out_best_point_distance_to_ray);
};
#ifdef __cplusplus
}
#endif
