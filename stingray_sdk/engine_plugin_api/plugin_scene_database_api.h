#pragma once

#ifdef CAN_COMPILE

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

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
	uint8_t bake_scale;
	SDB_SceneImportTangents tangents;
};

struct SD_Scene;
struct SDB_SceneDatabase;
struct SDB_Geometries;
typedef uint32_t SDB_ChannelType;

struct SceneDatabaseApi
{
	// Deprecated
	void (*scene)(SD_Scene *scene, SDB_SceneDatabase *dest, struct AllocatorObject *allocator);
	// Deprecated
	void (*set_scene)(SD_Scene *scene, const SDB_SceneDatabase *source);
	// Deprecated
	void (*geometries)(SD_Scene *scene, SDB_Geometries *dest, struct AllocatorObject *allocator);
	// Deprecated
	const char * (*source_path)(const SD_Scene *scene);
	// Deprecated
	void (*set_source_path)(SD_Scene *scene, const char *text);
	// Deprecated
	SDB_SceneImportOptions (*import_options)(SD_Scene *scene);
	// Deprecated
	void (*set_import_options)(SD_Scene *scene, const SDB_SceneImportOptions *source);

	/* Utilities */
	// Deprecated, use create_scene instead
	SD_Scene * (*create)(struct DataCompileParameters *params, const char *resource_name);
	// Deprecated, use destroy_scene instead
	void (*destroy)(SD_Scene *scene);
	// Deprecated
	uint32_t (*channel_size)(SDB_ChannelType channel_type);

	// Deprecated, use apply_scene_modifiers instead
	void (*apply_modifiers)(SD_Scene *scene, const char *platform_name, const char *resource_name, bool modify_tangents);

	// Deprecated
	void (*convert_scene)(SD_Scene *dest_scene, const struct ST_SceneDatabase *src_scene);
	void (*apply_scene_modifiers)(struct ST_SceneDatabase *scene, const char *platform_name, const char *resource_name, bool modify_tangents);
	ST_SceneDatabase * (*create_scene)(struct DataCompileParameters *params, const char *resource_name);
	const char * (*load_scene)(ST_SceneDatabase *scene, struct DataCompileParameters *params, const char *resource_name);
	void (*destroy_scene)(ST_SceneDatabase *scene);
};

#endif /* CAN_COMPILE */
