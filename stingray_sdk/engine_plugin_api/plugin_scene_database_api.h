#pragma once

#ifdef CAN_COMPILE

struct ST_SceneDatabase;

struct SceneDatabaseApi
{
	void (*apply_scene_modifiers)(struct ST_SceneDatabase *scene, const char *platform_name, const char *resource_name, bool modify_tangents);
	struct ST_SceneDatabase * (*create_scene)(struct DataCompileParameters *params, const char *resource_name);
	const char * (*load_scene)(struct ST_SceneDatabase *scene, struct DataCompileParameters *params, const char *resource_name);
	void (*destroy_scene)(struct ST_SceneDatabase *scene);
};

#endif /* CAN_COMPILE */
