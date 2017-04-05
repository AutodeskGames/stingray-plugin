#pragma once

#ifdef CAN_COMPILE

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

enum SDB_ChannelType {
	SDCT_FLOAT1 = 0,
	SDCT_FLOAT2,
	SDCT_FLOAT3,
	SDCT_FLOAT4,
	SDCT_MATRIX4x4,
	SDCT_QUATERNION,
	SDCT_FLOAT3_CMP_11_11_10,
	SDCT_HALF1,
	SDCT_HALF2,
	SDCT_HALF3,
	SDCT_HALF4,
	SDCT_UBYTE4,
	SDCT_SHORT1,
	SDCT_SHORT2,
	SDCT_SHORT3,
	SDCT_SHORT4,
	SDCT_COUNT
};

/* Direct Access, No extra memory copy */
struct SD_Scene;
struct SD_Indices;
struct SD_Geometry;
struct SD_GeometryMaterial;
struct SD_Animation;
struct SD_AnimationTake;
struct SD_Stream;
struct SD_Channel;
struct SD_BlendShapeTarget;
struct SD_Streams;

/* Indirect Access, Copy memory */
struct SDB_StringList {
	uint32_t size;
	const char **data;
};

struct SDB_Channel {
	const char *name;
	uint32_t index;
	SDB_ChannelType type;
};

struct SDB_Stream {
	uint32_t n_channels;
	SDB_Channel *channels;
	uint32_t size;
	uint32_t stride;
	uint32_t n_data;
	uint8_t *data;
};

struct SDB_Node {
	const char *name;
	const char *parent;
	SDB_StringList children;
	float local[16];
	SDB_StringList geometries;
	uint8_t viewport_visible;
	uint8_t has_local_mirroring;
};

struct SDB_IndicesStream {
	uint32_t n_indices;
	uint32_t *indices;
};

struct SDB_Indices {

	uint32_t n_indices;
	uint32_t n_streams;
	SDB_IndicesStream *streams;
};

struct SDB_Joint {
	const char *name;
	float inv_bind_matrix[16];
};

struct SDB_Skin {
	const char *name;
	uint32_t max_affecting_bones;
	uint32_t n_joints;
	SDB_Joint *joints;
};

struct SDB_GeometryInstance {
	const char *name;
	const char *geometry;
	SDB_StringList materials;
};

struct SDB_GeometryMaterial {
	const char *name;
	uint32_t n_primitives;
	uint32_t *primitives;
};

struct SDB_GeometryBlendShapeTarget {
	const char *name;
	uint32_t n_streams;
	SDB_Stream *streams;
};

struct SDB_Geometry {
	const char *name;
	uint32_t n_streams;
	SDB_Stream *streams;
	SDB_Indices indices;
	const char *skin;
	uint32_t n_materials;
	SDB_GeometryMaterial *materials;
	uint32_t n_primitive_smoothing;
	uint32_t *primitive_smoothing;
	uint32_t n_blend_shape_targets;
	SDB_GeometryBlendShapeTarget *blend_shape_targets;
	uint8_t shadow_caster;
	uint32_t n_vertex_position_remapping;
	uint32_t *vertex_position_remapping;
	uint32_t n_vertex_normal_remapping;
	uint32_t *vertex_normal_remapping;
};

enum SDB_LightDefinitionType {
	OMNI = 0,
	SPOT = 1,
	BOX = 2,
	DIRECTIONAL = 3
};
struct SDB_Light {
	const char *name;
	SDB_LightDefinitionType type;
	float color[4];
	float falloff_start;
	float falloff_end;
	float spot_angle_start;
	float spot_angle_end;
	uint8_t cast_shadow;
};

enum SDB_CameraDefinitionType {
	ORTHOGRAPHIC,
	PERSPECTIVE
};
struct SDB_Camera {
	const char *name;
	SDB_CameraDefinitionType type;
	float near_plane;
	float far_plane;
	float vertical_fov;
};

struct SDB_Animation {
	const char *node;
	const char *parameter;
	uint32_t n_times;
	float *times;
	SDB_Stream data;
};

struct SDB_AnimationTake {
	const char *name;
	float start_time;
	float end_time;
	uint32_t nb_samples;
	uint32_t n_animations;
	SDB_Animation *animations;
};

struct SDB_SurfaceMaterialProperty {
	const char *name;
	uint32_t n_integers;
	int integer;
	uint32_t n_floats;
	float floats[4];
	const char *value_string;
	SDB_StringList textures;
};

struct SDB_SurfaceMaterialProperties {
	uint32_t size;
	SDB_SurfaceMaterialProperty *data;
};

enum SDB_SurfaceMaterialDefinitionType {
	LAMBERT = 0,
	PHONG   = 1,
	SHADER  = 2
};
struct SDB_SurfaceMaterial {
	const char *name;
	SDB_SurfaceMaterialDefinitionType type;
	SDB_SurfaceMaterialProperties properties;
	uint32_t nb_influences;
};

struct SDB_Texture {
	const char *name;
	const char *file_path;
	const char *relative_path;
	uint8_t embedded;
	float uv_offset[2];
	float uv_scale[2];
	float uv_rotation;
};

struct SDB_LevelOfDetailStep {
	SDB_StringList nodes;
	float min_pct;
	float max_pct;
};

struct SDB_LevelOfDetail {
	const char *name;
	const char *orientation_node;
	const char *bounding_volume;
	uint8_t requires_predefined_pct;
	uint32_t n_steps;
	SDB_LevelOfDetailStep *steps;
};

enum SDB_SceneImportTangents {
	TANGENTS_IMPORT,
	TANGENTS_MIKKTSPACE
};
struct SDB_SceneImportOptions {
	uint8_t combine_meshes;
	uint8_t combine_meshes_by_material;
	uint8_t reverse_forward_axis;
	uint8_t skip_create_extra_root;
	uint8_t skip_textures;
	uint8_t skip_lights;
	uint8_t skip_cameras;
	uint8_t create_missing_uvs;
	SDB_SceneImportTangents tangents;
};

struct SDB_Property {
	const char *first;
	const char *second;
};

struct SDB_Nodes {
	uint32_t size;
	SDB_Node *data;
};

struct SDB_GeometryInstances {
	uint32_t size;
	SDB_GeometryInstance *data;
};

struct SDB_Geometries {
	uint32_t size;
	SDB_Geometry *data;
};

struct SDB_Lights {
	uint32_t size;
	SDB_Light *data;
};

struct SDB_Cameras {
	uint32_t size;
	SDB_Camera *data;
};

struct SDB_Skins {
	typedef SDB_Skin value_type;
	uint32_t size;
	SDB_Skin *data;
};

struct SDB_SurfaceMaterials {
	uint32_t size;
	SDB_SurfaceMaterial *data;
};

struct SDB_Textures {
	uint32_t size;
	SDB_Texture *data;
};

struct SDB_LevelOfDetails {
	uint32_t size;
	SDB_LevelOfDetail *data;
};

struct SDB_AnimationTakes {
	uint32_t size;
	SDB_AnimationTake *data;
};

struct SDB_Properties {
	uint32_t size;
	SDB_Property *data;
};

struct SDB_SceneDatabase {
	SDB_Nodes nodes;
	SDB_StringList roots;
	SDB_GeometryInstances geometry_instances;
	SDB_Geometries geometries;
	SDB_Lights lights;
	SDB_Cameras cameras;
	SDB_Skins skins;
	SDB_SurfaceMaterials materials;
	SDB_Textures textures;
	SDB_LevelOfDetails lods;
	SDB_AnimationTakes anim_takes;
	const char *source_path;
	SDB_SceneImportOptions import_options;
	SDB_Properties properties;
};

struct SceneDatabaseApi
{
	void (*scene)(SD_Scene *scene, SDB_SceneDatabase *dest, struct AllocatorObject *allocator);
	void (*set_scene)(SD_Scene *scene, const SDB_SceneDatabase *source);

	void (*geometries)(SD_Scene *scene, SDB_Geometries *dest, struct AllocatorObject *allocator);

	const char * (*source_path)(const SD_Scene *scene);
	void (*set_source_path)(SD_Scene *scene, const char *text);

	SDB_SceneImportOptions (*import_options)(SD_Scene *scene);
	void (*set_import_options)(SD_Scene *scene, const SDB_SceneImportOptions *source);

	/* Utilities */
	SD_Scene * (*create)(struct DataCompileParameters *params, const char *resource_name);
	void (*destroy)(SD_Scene *scene);

	uint32_t (*channel_size)(SDB_ChannelType channel_type);

	void (*apply_modifiers)(SD_Scene *scene, const char *platform_name, const char *resource_name, bool modify_tangents);
};

#endif /* CAN_COMPILE */
