#pragma once

#include "plugin_api_types.h"
#include "plugin_c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdint.h>

/*
	This file defines the Plugin API for the engine.

	The plugin interface is based around a single function:

		__declspec(dllexport) void *get_plugin_api(unsigned api_id);

	The API ID is an integer that uniquely identify a specific version of a particular service.
	If the plugin can provide the service it returns a pointer to an API struct that contains
	function pointers for using the service.

	For ABI compatibility and simplicity, only C code is used in the interfaces.

	This method is used both by the plugins to provide services to the engine and by the engine
	to provide services to the plugins. For the second case, the engine sends a function:

		void *get_engine_api(unsigned api_id);

	to the plugins when they are initialized. The plugins can use this function to query for
	engine interfaces. Plugins can also use this to call on services provided by other plugins
	through the get_next_plugin_api() in the PluginManagerApi.

	Starting with the 1.7 release of the engine, we will make an effort to keep the plugin
	APIs backwards compatible. This means that you cannot remove functions or change the
	signature of functions in the API, only add new ones in the reserved functions. Old functions
	can be marked as deprecated but should be left in the API.

	If you need to make big changes to an API, that cannot easily be covered by just adding
	new functions, you should make a completely new API with a new ID (i.e.
	APPLICATION_API_V2_ID), while keeping the old one intact. That way, backwards compatibility
	is ensured.
*/

#include <stddef.h>

/* API IDs for the different services. */
enum PluginApiID {
	PLUGIN_API_ID =						0,
	LUA_API_ID =						1,
	DATA_COMPILER_API_ID =				2,
	DATA_COMPILE_PARAMETERS_API_ID =	3,
	ALLOCATOR_API_ID =					4,
	RESOURCE_MANAGER_API_ID =			5,
	LOGGING_API_ID =					6,
	UNIT_API_ID =						8,
	SCENE_GRAPH_API_ID =				9,
	FUTURE_INPUT_ARCHIVE_API_ID =		10,
	INPUT_ARCHIVE_API_ID =				11,
	APPLICATION_API_ID =				12,
	APPLICATION_OPTIONS_API_ID =		13,
	UNIT_REFERENCE_API_ID =				14,
	ERROR_CONTEXT_API_ID =				15,
	RENDER_INTERFACE_API_ID =			16,
	RAYCAST_API_ID =					17,
	RENDER_CALLBACKS_PLUGIN_API_ID =	18,
	RENDER_OVERRIDES_PLUGIN_API_ID =	19,
	FILESYSTEM_API_ID =					20,
	PLUGIN_MANAGER_API_ID =				21,
	WORLD_API_ID =						22,
	LINE_OBJECT_DRAWER_API_ID =			23,
	PROFILER_API_ID =					24,
	ERROR_API_ID =						25,
	RENDER_BUFFER_API_ID =				26,
	MESH_API_ID =						27,
	INPUT_BUFFER_API_ID =				28,
	RENDER_SCENE_GRAPH_API_ID =			29,
	SOUND_STREAM_SOURCE_API_ID =		30,
	C_API_ID =							31,
	THREAD_API_ID =						32,
	TIMER_API_ID =						33,
	MATERIAL_API_ID =					34,
	SCENE_DATABASE_API_ID =				35,
	STREAM_CAPTURE_API_ID =				36,
	FLOW_NODES_API_ID =					37,
	CAMERA_API_ID =						38,
	ENTITY_COMPILE_DATA_API_ID =		39,
	PHYSICS_RUNTIME_COOKING_API_ID =	40,
	END_OF_ENGINE_RESERVED_RANGE =		65535,

	/* API IDs in the range 0--65535 are reserved by the engine. If you want to
	   provide your own API in your plugin, we suggest using a hash of the API's
	   name as ID. */
};

/* ----------------------------------------------------------------------
	Common types
---------------------------------------------------------------------- */

/* These types are used in multiple plugins. */

/* Opaque struct representing an input file archive that data can be read from. */
struct InputArchive;

/* Opaque struct representing a buffer that an input archive gets information from. */
struct InputBuffer;

/* ----------------------------------------------------------------------
	Plugin
---------------------------------------------------------------------- */

/* This function can be used by the plugin to query for engine APIs. */
typedef void *(*GetApiFunction)(unsigned api);

/* Opaque struct representing a stream of state changes sent from the main thread to the render
	thread. */
struct StateReflectionStream;

/* Deprecated. */
struct RD_DeviceData {
	struct Context *context;
	struct RenderTarget* render_target;
	struct DepthStencilTarget* depth_stencil_target;
};

/* Deprecated. */
struct RD_EngineData {
	/* A custom rendering environment returned by the plugin in get_render_env(). */
	void* render_env;
	void* render_target;
	void* depth_stencil_target;
};

/* Deprecated. */
struct RenderDevicePluginArguments {
	struct RD_DeviceData device_data;
	struct RD_EngineData engine_data;
};

/*
	This is the main interface provided by the plugins. The functions in this interface will
	be called at various points during the engine's setup and shutdown sequence.

	The plugin is not obligated to implement all these functions. You can return NULL for the
	functions that you do not support.
*/
struct PluginApi
{
	/* Returns the name of the plugin. */
	const char *(*get_name)();

	/* Called to initialize the plugin once it has been loaded into memory. For plugins loaded at
	   boot, this function is called once all plugins have been loaded (so you can query for other
		plugins in this function). For plugins loaded on demand, this function is called as soon
	   as the plugin have been loaded. */
	void (*loaded)(GetApiFunction get_engine_api);

	/* Called just before the plugin is unloaded. */
	void (*unloaded)();

	/* Called at the start of a "hot reload" of the plugin DLL. Should return a
	   pointer to a serialized "state" for the plugin.*/
	void *(*start_reload)(GetApiFunction get_engine_api);

	/* Called to finalized the "hot reload" after the plugin has been reloaded with
	   the new code. Should restore the state from the serialized state data. Note
	   that it is the responsibility of the plugin to free the state data. */
	void (*finish_reload)(GetApiFunction get_engine_api, void *state);

	/* Called when the engine sets up the DataCompiler. You can use the functions in the DataCompiler
	   API to add custom data types to the DataCompiler. */
	void (*setup_data_compiler)(GetApiFunction get_engine_api);

	/* Called when the engine shuts down the data compiler. */
	void (*shutdown_data_compiler)();

	/* Called when the engine sets up the ResourceManager. At this point you can use the ResourceManagerApi
	   to add support for resource manager loading of your custom data types. */
	void (*setup_resources)(GetApiFunction get_engine_api);

	/* Called when the engine shuts down the ResourceManager. */
	void (*shutdown_resources)();

	/* Called when the engine reloads its resources. The plugin should return true if it is able
	   to hot-reload resources of the specified type. */
	int (*can_refresh)(uint64_t type);

	/* Called when the engine reloads its resources, to tell the plugin to refresh the given resource. */
	void (*refresh)(uint64_t type, uint64_t name);

	/* Called when the engine sets up the game. At this point, you can use the functions in the LuaApi
	   to add functions to the engine's Lua API. */
	void (*setup_game)(GetApiFunction get_engine_api);

	/* Called per game frame. */
	void (*update_game)(float dt);

	/* Called when the engine shuts down the game. */
	void (*shutdown_game)();

	/* Called after the world has been created and is about to be added to the engines list of worlds */
	void (*register_world)(CApiWorld * world);

	/* Called before a world is about to be destroyed and removed from the engines list of worlds. */
	void (*unregister_world)(CApiWorld * world);

	/* Called when units are spawned by the engine. */
	void (*units_spawned)(CApiUnit **units, unsigned count);

	/* Called when units are unspawned by the engine. */
	void (*units_unspawned)(CApiUnit **units, unsigned count);

	/* Called by the engine to draw debug visuals into the world. */
	void (*debug_draw)(CApiWorld * world, struct StateReflectionStream * srs);

	/* Deprecated. */
	void * (*get_render_env)();

	/* Deprecated. */
	void (*render)(struct RenderDevicePluginArguments *arguments);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/*
	This is the interface implemented by plugins who are interested in callbacks from the rendering
	thread.

	The plugin is not obligated to implement all these functions. You can return NULL for the
	functions that you do not support.
*/
struct RenderCallbacksPluginApi
{
	/* Called when a new swapchain is created. */
	void (*create_swap_chain)(unsigned swap_chain_handle, unsigned width, unsigned height);

	/* Called just before a swap chain is resized. */
	void (*prepare_resize_swap_chain)(unsigned swap_chain_handle, unsigned width, unsigned height);

	/* Called when a swap chain has been resized. */
	void (*resize_swap_chain)(unsigned swap_chain_handle, unsigned width, unsigned height);

	/* Called when a swap chain is destroyed. */
	void (*destroy_swap_chain)(unsigned swap_chain_handle);

	/* Called when rendering of a frame starts. */
	void (*begin_frame)();

	/* Called when rendering of a frame finishes. */
	void (*end_frame)();

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/*
	This is the interface implemented by plugins who are interested in overriding certain functionality
	on the rendering thread.

	The plugin is not obligated to implement all these functions. You can return NULL for the
	functions that you do not support.

	TODO: How do we best deal with multiple plugins overriding the same function?
*/
struct RenderOverridesPluginApi
{
	/* Called when the engine presents the rendered data.

	   You should return 0 from this function if you still want the default present functionality
	   to be executed. Otherwise, return 1. */
	int (*present)(unsigned swap_chain_handle);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	Lua
---------------------------------------------------------------------- */

/* Opaque struct representing a Lua state. */
typedef struct lua_State lua_State;

/* Types from Lua. */
typedef int (*lua_CFunction) (lua_State *L);
typedef struct lua_Debug lua_Debug;
typedef double lua_Number;
typedef ptrdiff_t lua_Integer;
typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);
typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);
typedef int (*lua_Writer) (lua_State *L, const void* p, size_t sz, void* ud);
typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
typedef struct luaL_Reg luaL_Reg;

/*
	Interface to access Lua services.
*/
struct LuaApi
{
	/* -----------------------------------------------------------------------
		Extending Lua
	  ----------------------------------------------------------------------- */

	/* Adds a new lua function in the module with the specified name.

	   The function will be callable as stingray.{module}.{name}() */
	void (*add_module_function)(const char *module, const char *name, lua_CFunction f);

	/* As add_module_function() but prints a deprecation warning when the function is used. */
	void (*deprecated_warning)(const char *module, const char *name, lua_CFunction f, const char* message);

	/* As add_module_function() but prints a deprecation error when the function is used. */
	void (*deprecated_error)(const char *module, const char *name, const char* message);

	/* Sets a bool constant in a module. */
	void (*set_module_bool)(const char *module, const char *key, int value);

	/* Sets a number constant in a module. */
	void (*set_module_number)(const char *module, const char *key, double value);

	/* Sets a number constant in a namespace in a module. */
	void (*set_module_namespace_number)(const char *module, const char* name_space, const char *key, double value);

	/* Sets a string constant in a module. */
	void (*set_module_string)(const char *module, const char *key, const char *value);

	/* Adds a new console command. Console commands are Lua functions in the stingray.Console
	   module that only takes string parameters. They can be used from the console:

			> memory_resources all

	   is equivalent to

			> Console.memory_resources("all")

	   The vararg is a sequence of documentation strings, ended by a nullptr -- like this:

		add_console_command("memory_resources", memory_resources_f,
			"Print memory usage per resource",
			"all", "print memory use of all resources",
			"sound", "print memory use of sound resources",
			"texture_categories [details]", "print memory usage per texture category",
			"list <TYPE>", "list memory use of specified types",
			(void*)nullptr); */
	void (*add_console_command)(const char *command, lua_CFunction f, const char *desc, ...);

	/* Removes all entries from the specified module. */
	void (*remove_all_module_entries)(const char *module);

	/* Removes the specified module entry from the runtime. */
	void (*remove_module_entry)(const char *module, const char *entry);

	/* -----------------------------------------------------------------------
		Lua standard functions

		See the Lua API for documentation.
	  ----------------------------------------------------------------------- */

	/* State manipulation */
	void		  (*close)     (lua_State *L);
	lua_State	 *(*newthread) (lua_State *L);
	lua_CFunction (*atpanic)   (lua_State *L, lua_CFunction panicf);

	/* Basic stack manipulation */
	int   (*gettop) (lua_State *L);
	void  (*settop) (lua_State *L, int idx);
	void  (*pushvalue) (lua_State *L, int idx);
	void  (*remove) (lua_State *L, int idx);
	void  (*insert) (lua_State *L, int idx);
	void  (*replace) (lua_State *L, int idx);
	int   (*checkstack) (lua_State *L, int sz);
	void  (*xmove) (lua_State *from, lua_State *to, int n);

	/* Access functions */
	int             (*isnumber) (lua_State *L, int idx);
	int             (*isstring) (lua_State *L, int idx);
	int             (*iscfunction) (lua_State *L, int idx);
	int             (*isuserdata) (lua_State *L, int idx);
	int             (*type) (lua_State *L, int idx);
	const char     *(*lua_typename) (lua_State *L, int tp);

	int            (*equal) (lua_State *L, int idx1, int idx2);
	int            (*rawequal) (lua_State *L, int idx1, int idx2);
	int            (*lessthan) (lua_State *L, int idx1, int idx2);

	lua_Number		(*tonumber) (lua_State *L, int idx);
	lua_Integer  	(*tointeger) (lua_State *L, int idx);
	int             (*toboolean) (lua_State *L, int idx);
	const char     *(*tolstring) (lua_State *L, int idx, size_t *len);
	size_t          (*objlen) (lua_State *L, int idx);
	lua_CFunction   (*tocfunction) (lua_State *L, int idx);
	void	       *(*touserdata) (lua_State *L, int idx);
	lua_State      *(*tothread) (lua_State *L, int idx);
	const void     *(*topointer) (lua_State *L, int idx);

	/* Push functions */
	void  (*pushnil) (lua_State *L);
	void  (*pushnumber) (lua_State *L, lua_Number n);
	void  (*pushinteger) (lua_State *L, lua_Integer n);
	void  (*pushlstring) (lua_State *L, const char *s, size_t l);
	void  (*pushstring) (lua_State *L, const char *s);
	const char *(*pushvfstring) (lua_State *L, const char *fmt, va_list argp);
	const char *(*pushfstring) (lua_State *L, const char *fmt, ...);
	void  (*pushcclosure) (lua_State *L, lua_CFunction fn, int n);
	void  (*pushboolean) (lua_State *L, int b);
	void  (*pushlightuserdata) (lua_State *L, void *p);
	int   (*pushthread) (lua_State *L);

	/* Get functions */
	void  (*gettable) (lua_State *L, int idx);
	void  (*getfield) (lua_State *L, int idx, const char *k);
	void  (*rawget) (lua_State *L, int idx);
	void  (*rawgeti) (lua_State *L, int idx, int n);
	void  (*createtable) (lua_State *L, int narr, int nrec);
	void *(*newuserdata) (lua_State *L, size_t sz);
	int   (*getmetatable) (lua_State *L, int objindex);
	void  (*getfenv) (lua_State *L, int idx);

	/* Set functions */
	void  (*settable) (lua_State *L, int idx);
	void  (*setfield) (lua_State *L, int idx, const char *k);
	void  (*rawset) (lua_State *L, int idx);
	void  (*rawseti) (lua_State *L, int idx, int n);
	int   (*setmetatable) (lua_State *L, int objindex);
	int   (*setfenv) (lua_State *L, int idx);

	/* Load and call functions */
	void  (*call) (lua_State *L, int nargs, int nresults);
	int   (*pcall) (lua_State *L, int nargs, int nresults, int errfunc);
	int   (*cpcall) (lua_State *L, lua_CFunction func, void *ud);
	int   (*load) (lua_State *L, lua_Reader reader, void *dt, const char *chunkname);
	int   (*dump) (lua_State *L, lua_Writer writer, void *data);

	/* Coroutine functions */
	int  (*yield) (lua_State *L, int nresults);
	int  (*resume) (lua_State *L, int narg);
	int  (*status) (lua_State *L);

	/* Garbage collection */
	int (*gc) (lua_State *L, int what, int data);

	/* Miscellaneous functions */
	int   (*error) (lua_State *L);
	int   (*next) (lua_State *L, int idx);
	void  (*concat) (lua_State *L, int n);

	/* Debugging */
	int (*getstack) (lua_State *L, int level, lua_Debug *ar);
	int (*getinfo) (lua_State *L, const char *what, lua_Debug *ar);
	const char *(*getlocal) (lua_State *L, const lua_Debug *ar, int n);
	const char *(*setlocal) (lua_State *L, const lua_Debug *ar, int n);
	const char *(*getupvalue) (lua_State *L, int funcindex, int n);
	const char *(*setupvalue) (lua_State *L, int funcindex, int n);

	int (*sethook) (lua_State *L, lua_Hook func, int mask, int count);
	lua_Hook (*gethook) (lua_State *L);
	int (*gethookmask) (lua_State *L);
	int (*gethookcount) (lua_State *L);

	/* Library functions */
	void (*lib_openlib) (lua_State *L, const char *libname, const luaL_Reg *l, int nup);
	void (*lib_register) (lua_State *L, const char *libname, const luaL_Reg *l);
	int	 (*lib_getmetafield) (lua_State *L, int obj, const char *e);
	int	 (*lib_callmeta) (lua_State *L, int obj, const char *e);
	int (*lib_typerror) (lua_State *L, int narg, const char *tname);
	int	 (*lib_argerror) (lua_State *L, int numarg, const char *extramsg);
	const char	*(*lib_checklstring) (lua_State *L, int numArg, size_t *l);
	const char	*(*lib_optlstring) (lua_State *L, int numArg, const char *def, size_t *l);
	lua_Number	 (*lib_checknumber) (lua_State *L, int numArg);
	lua_Number	 (*lib_optnumber) (lua_State *L, int nArg, lua_Number def);
	lua_Integer	 (*lib_checkinteger) (lua_State *L, int numArg);
	lua_Integer	 (*lib_optinteger) (lua_State *L, int nArg, lua_Integer def);
	void (*lib_checkstack) (lua_State *L, int sz, const char *msg);
	void (*lib_checktype) (lua_State *L, int narg, int t);
	void (*lib_checkany) (lua_State *L, int narg);
	int	 (*lib_newmetatable) (lua_State *L, const char *tname);
	void*(*lib_checkudata) (lua_State *L, int ud, const char *tname);
	void (*lib_where) (lua_State *L, int lvl);
	int (*lib_error) (lua_State *L, const char *fmt, ...);
	int	 (*lib_checkoption) (lua_State *L, int narg, const char *def, const char *const lst[]);
	int	 (*lib_ref) (lua_State *L, int t);
	void (*lib_unref) (lua_State *L, int t, int ref);
	int	 (*lib_loadfile) (lua_State *L, const char *filename);
	int (*lib_loadbuffer) (lua_State *L, const char *buff, size_t sz, const char *name);
	int (*lib_loadstring) (lua_State *L, const char *s);
	lua_State *(*lib_newstate) (void);
	const char *(*lib_gsub) (lua_State *L, const char *s, const char *p, const char *r);
	const char *(*lib_findtable) (lua_State *L, int idx, const char *fname, int szhint);
	void (*lib_openlibs)(lua_State *L);

	/* -----------------------------------------------------------------------
		Lua Stingray extensions
	  ----------------------------------------------------------------------- */

	/* Gets an index integer from the stack. This will automatically convert
	   from 1-based (Lua convention) to 0-based (C convention). */
	int (*getindex) (lua_State *L, int idx);

	/* Pushes an index integer to the stack. This will automatically convert
	   from 0-based (C convention) to 1-based (lua convention). */
	void (*pushindex) (lua_State *L, int n);

	/* As getindex() but uses either 0 or 1 based convention on the Lua side,
	   depending on user project settings. */
	int (*getindex_0_or_1_based) (lua_State *L, int idx);

	/* As pushindex() but uses either 0 or 1 based convention on the Lua side,
	   depending on user project settings. */
	void (*pushindex_0_or_1_based) (lua_State *L, int n);

	/* Pushes a Vector2 to the stack. */
	void  (*pushvector2) (lua_State *L, float v[2]);

	/* Pushes a Vector3 to the stack. */
	void  (*pushvector3) (lua_State *L, float v[3]);

	/* Pushes a Vector4 to the stack. */
	void  (*pushvector4) (lua_State *L, float v[4]);

	/* Pushes a Quaternion to the stack. */
	void  (*pushquaternion) (lua_State *L, float q[4]);

	/* Pushes a Matrix4x4 to the stack. */
	void  (*pushmatrix4x4) (lua_State *L, float m[16]);

	/* Gets a Vector2 at the specified index. */
	float * (*getvector2) (lua_State *L, int i);

	/* Gets a Vector3 at the specified index. */
	float * (*getvector3) (lua_State *L, int i);

	/* Gets a Vector4 at the specified index. */
	float * (*getvector4) (lua_State *L, int i);

	/* Gets a Quaternion at the specified index. */
	float * (*getquaternion) (lua_State *L, int i);

	/* Gets a Matrix4x4 at the specified index. */
	float * (*getmatrix4x4) (lua_State *L, int i);

	/* Gets a Unit at the specified index. */
	CApiUnit * (*getunit) (lua_State *L, int i);

	/* Gets an Entity at the specified index. */
	EntityRef (*getentity)(lua_State *L, int i);

	/* Pushes an Entity to the stack. */
	void (*pushentity)(lua_State *L, EntityRef e_ref);

	/* Gets the Lua state where the main scripts execute. */
	lua_State* (*getscriptenvironmentstate)();

	/* Returns true if the stack entry is a nil. */
	int(*isnil) (lua_State *L, int i);

	/* Returns true if the stack entry is a boolean. */
	int(*isbool) (lua_State *L, int i);

	/* Returns true if the stack entry is a table. */
	int (*istable) (lua_State *L, int i);

	/* Returns true if the stack entry is a Vector2. */
	int (*isvector2) (lua_State *L, int i);

	/* Returns true if the stack entry is a Vector3. */
	int (*isvector3) (lua_State *L, int i);

	/* Returns true if the stack entry is a Vector4. */
	int (*isvector4) (lua_State *L, int i);

	/* Returns true if the stack entry is a Quaternion. */
	int (*isquaternion) (lua_State *L, int i);

	/* Returns true if the stack entry is a Matrix4x4. */
	int (*ismatrix4x4) (lua_State *L, int i);

	/* Returns true if the stack entry is a UnitReference. */
	int (*isunitreference) (lua_State *L, int i);

	/* Pops the top value from the Lua stack. */
	void (*pop) (lua_State *L);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	DataCompiler
---------------------------------------------------------------------- */

/* Represents a buffer of data. */
struct Buffer
{
	/* Pointer to data. */
	char *p;

	/* Size of data. */
	unsigned len;
};

struct ConfigErrorState
{
	const char *file;
	struct Buffer source;
	const char *error;
};

/* Represents the result of a data compile operation. */
struct DataCompileResult
{
	/* The memory resident compiled data. */
	struct Buffer data;

	/* Compiled data available for streaming. */
	struct Buffer stream;

	/* NULL if compiled successfully, an error message otherwise. */
	const char *error;
};

/* Opaque struct representing parameters for a data compile operation. */
struct DataCompileParameters;

/* Opaque struct representing parameters for a entity compile operation. */
struct EntityComponentCompileData;

/* Opaque struct representing parameters for a entity compile operation. */
struct EntityComponentPackageIncludeData;

/* Function type for compiling data. Based on the compile parameters that include
	among other things the source data, the compile function should produce a
	binary blob that can be accessed as a resource by the runtime. */
typedef struct DataCompileResult (*CompileFunction)(struct DataCompileParameters *data_compile_params);

/* Function for compiling preprocessed data for a closed platform. This is called from a normal
	resource compiler to do closed platform specific compilation for a particular platform. The
	format of the input data depends on the resource type (note: it is not the raw source data). */
typedef struct DataCompileResult (*RawCompileFunction)(const char *input, unsigned len, struct AllocatorObject *allocator);

/* Function type for compiling additional dependencies. You can use this to add new dependencies
	for an existing resource type, such as .level, without changing how that type is compiled.
	The function should return NULL if successful and an error string otherwise. */
typedef const char * (*PackageIncludeCompileFunction)(struct DataCompileParameters *data_compile_params);

/* Function type for compiling entity component data. */
typedef struct DataCompileResult (*EntityComponentCompileFunction)(struct EntityComponentCompileData *compile_data, struct EntityComponentPackageIncludeData *package_include_data);

/* Enumerates the texture types that can be returned by custom texture readers. */
enum SourceTextureReadResult_ResultType {
	DC_STRR_RT_IMAGE2D,
	DC_STRR_RT_IMAGE3D,
	DC_STRR_RT_IMAGECUBE,
	DC_STRR_RT_UNKNOWN
};

/* Enumerates the texture pixel formats that can be returned by customer texture readers. */
enum SourceTextureReadResult_ResultPixelFormat {
	DC_STRR_RPF_R8G8B8A8,
	DC_STRR_RPF_R16F,
	DC_STRR_RPF_R16G16B16A16F,
	DC_STRR_RPF_R16G16F,
	DC_STRR_RPF_NUM_FORMATS,
	DC_STRR_RPF_UNKNOWN
};

/* Format of the texture data returned by custom texture readers. Currently only one format is
	supported, the one described by SourceTextureReadResult */
#define SOURCE_TEXTURE_READ_RESULT_DEFAULT_FORMAT 1

/* Used to return the result of a custom texture read operation. */
struct SourceTextureReadResult {
	/* Format of the returned data. This should be equal to SOURCE_TEXTURE_READ_RESULT_DEFAULT_FORMAT. */
	unsigned format;

	/* Texture dimensions. */
	unsigned width;
	unsigned height;

	/* Format of the pixel data. */
	enum SourceTextureReadResult_ResultPixelFormat pixel_format;

	/* Type of image. */
	enum SourceTextureReadResult_ResultType image_type;

	/* Pixel data container. */
	struct Buffer data;

	/* NULL if read successfully, an error message otherwise. */
	const char *error;
};

/* Function type for custom texture readers. */
typedef struct SourceTextureReadResult (*SourceTextureReadFunction)(const char *type, const void *data, unsigned len, struct AllocatorObject *allocator);

/*
	API for extending Stingray with your own custom data types.
*/
struct DataCompilerApi
{
	/* Adds a data compiler for a new data type to the Stingray engine. The version
	   parameter specifies the version number of the binary data. Increase the number if
	   you make any changes to the binary format. */
	void (*add_compiler)(const char *type, unsigned version, CompileFunction compile);

	/* Adds a data compiler for one of the closed platforms (XB1, PS4). (Since these
	   compilers contain closed code, they can't be in the main engine, but must be
	   loaded as plugins. */
	void (*add_closed_platform_compiler)(const char *platform, const char *type, RawCompileFunction compile);

	/* Adds a compile step that can add additional dependencies to an existing resource format,
	   without otherwise changing how that resource format is compiled. For example, it can be
	   used to add new dependencies to .level files. */
	void (*add_extra_package_include_compiler)(const char *type, int id, int version, PackageIncludeCompileFunction compile);

	/* Adds a new texture reader to Stingray. This lets Stingray support additional texture
	   formats. */
	void (*add_texture_reader)(const char *type, SourceTextureReadFunction read);

	/* Specifies that the compiler for the specified type uses the FBX SDK. This is needed because
	   the FBX SDK is not thread safe, so compilers that use the FBX SDK must be serialized
	   on a single thread. */
	void (*set_uses_fbx)(const char *type);

	/* Adds an entity component compiler for the specified component typename. */
	void(*add_entity_component_compiler)(const char *name, EntityComponentCompileFunction compile, int spawn_order);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	DataCompileParameters
---------------------------------------------------------------------- */

/*
	Used to get information about a resource that is being compiled.
*/
struct DataCompileParametersApi
{
	/* Path to the resource on disk. */
	const char * (*source_path)(struct DataCompileParameters *input);

	/* Name of the resource. */
	const char * (*name)(struct DataCompileParameters *input);

	/* Gets the string name of the destination platform that the data is compiled for. */
	const char * (*destination_platform)(struct DataCompileParameters *input);

	/* Parses the input data as a SJSON file and returns a buffer describing the data.
	   The buffer uses the ConstConfig format and can be interpreted using the ConstConfig
	   API in plugin_foundation. */
	struct DataCompileResult (*parse)(struct DataCompileParameters *input);

	/* Reads the input data and returns it as a raw buffer. */
	struct DataCompileResult (*read)(struct DataCompileParameters *input);

	/* Used to read the content of file folders, i.e. folders that are treated as a single
	   resource by the data compiler (like .s2d folders).

	   The entire content of the folder will be returned in a buffer with the following layout:

	   		[number_of_files]
			[offset_to_path_1] [size_of_path_1] [offset_to_file_data_1] [size_of_file_data_1]
			[offset_to_path_2] [size_of_path_2] [offset_to_file_data_2] [size_of_file_data_2]
			...
			[offset_to_path_n] [size_of_path_n] [offset_to_file_data_n] [size_of_file_data_n]
			[buffer_data]

	   All the sizes and offsets are uint32_t. */
	struct DataCompileResult (*read_file_folder)(struct DataCompileParameters *input);

	/* Returns the allocator that should be used to allocate the data returned by the compile
	   function. */
	struct AllocatorObject *(*allocator)(struct DataCompileParameters *input);

	/* Creates a package include of the resource specified by (type, name) for the resource that
	   is being compiled. What this means is that the compiled resource has an automatic dependency
	   on (type, name), so whenever the compiled resource is included in a package, its
	   dependencies will follow. This is used for example to ensure that when you include a level
	   in a package, all its units and their textures follow along. */
	void (*include_in_package)(struct DataCompileParameters *input, const char *type, const char *name);

	/* Creates a package include of all the resources of the type that match the pattern
	   `{prefix}*{suffix}`. */
	void (*glob_include_in_package)(struct DataCompileParameters *input, const char *prefix, const char *suffix, const char *type);

	/* Returns true if the path exists. */
	int (*exists)(struct DataCompileParameters *input, const char *path);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	EntityCompileDataApi
---------------------------------------------------------------------- */

/* API for working with entity compile data. */
struct EntityCompileDataApi
{
	/* Returns the allocator to use for compiled data. */
	struct AllocatorObject *(*allocator)(struct EntityComponentCompileData *compile_data);

	/* Returns the component type definition. */
	struct Buffer (*type_definition)(struct EntityComponentCompileData *compile_data, struct AllocatorObject *allocator);

	/* Returns the component meta data. */
	struct Buffer (*type_metadata)(struct EntityComponentCompileData *compile_data, struct AllocatorObject *allocator);

	/* Returns the property for the specified property key. */
	struct Buffer (*get_property)(struct EntityComponentCompileData *compile_data, const char *property_key, struct AllocatorObject *allocator, struct ConfigErrorState *es);

	/* Returns the merged property for the specified property key. */
	struct Buffer (*get_merged_property)(struct EntityComponentCompileData *compile_data, const char *property_key, struct AllocatorObject *allocator, struct ConfigErrorState *es);
};

/* ----------------------------------------------------------------------
	Allocator
---------------------------------------------------------------------- */

/*
	API used to allocate memory through an AllocatorObject.
*/
struct AllocatorApi
{
	/* Create a new allocator for use by the plugin. */
	struct AllocatorObject *(*make_plugin_allocator)(const char *plugin_name);

	/* Destroys an allocator created by make_plugin_allocator(). You must free all the memory
	   allocated by the allocator before you destroy it. */
	void (*destroy_plugin_allocator)(struct AllocatorObject *);

	/* Makes a physical allocator for the plugin. This is an allocator that is guaranteed to
	   allocate physical (i.e. not virtual) memory. This is needed by certain resource
	   types that cannot reside in virtual memory.

	   The allocator should be destroyed by destroy_plugin_allocator(). */
	struct AllocatorObject *(*make_plugin_physical_allocator)(const char *plugin_name);

	/* Creates a temporary memory allocator. Temporary memory allocators should be used
	   for short-term memory allocations that are released before a function exits (i.e.
	   similar to alloca()). Allocations made with the temporary memory allocator do not
	   have to be explicitly freed. They are automatically freed when you destroy the allocator.

	   You should call destroy_temp_allocator() to destroy the allocator before exiting the
	   function.

	   Temporary allocators are not thread safe and can only be used on the thread that creates
	   them. */
	struct AllocatorObject *(*make_temp_allocator)();

	/* Destroys a temporary memory allocator created by make_temp_allocator(). */
	void (*destroy_temp_allocator)(struct AllocatorObject *);

	/* Allocates memory using the specified allocator. The align parameter specifies the
	   desired alignment of the allocated memory. */
	void *(*allocate)(struct AllocatorObject *allocator, size_t size, unsigned align);

	/* Frees memory allocated by allocate(). */
	size_t (*deallocate)(struct AllocatorObject *allocator, void *p);

	/* Returns the size of the memory block allocated at p. p must be a block of memory allocated
	   by the specified allocator. Note that the allocated_size() might be greater than the size
	   requested in the call to allocate(). (Some allocators round up the allocations.) */
	size_t (*allocated_size)(struct AllocatorObject *allocator, void *p);
};

/* ----------------------------------------------------------------------
	ResourceManager
---------------------------------------------------------------------- */

/* Opaque struct representing an InputArchive that will become readable at some point in the
	future. */
struct FutureInputArchive;

/* Hashed version of a resource names. */
typedef uint64_t ResourceID;

/* Opaque struct representing a context in which changes can be applied to GPU residing resources. */
struct RenderResourceContext;

/* Struct of callbacks used to implement a custom resource type on the runtime side. You don't
	need to implement all the functions in this interface. Use NULL for the functions you don't
	implement. */
struct RM_ResourceTypeCallbacks
{
	/* User data that will be supplied to you in the obj parameter of the callback functions. */
	void *user_data;

	/* Called to load a resource into memory. `name` is the name of the resource and `archive` its
	   serialized data. The function should allocate an in-memory representation of the resource
	   with the `allocator` and return it.

	   You only need to implement this callback if you want the in-memory representation to be
	   different than the disk serialized one. The recommendation is to use the same format on
	   disk as in-memory. Then you can use NULL for this callback and the disk data will
	   automatically be loaded into memory. */
	void *(*load) (void *obj, ResourceID name, struct InputArchive *archive, struct AllocatorObject *allocator, struct RenderResourceContext *rrc);

	/* A companion to load(), this is used to destroy the in-memory representation. You only need
	   to implement this if you implement load(), to destroy the data allocated by load(). */
	void (*destroy) (void *obj, void *resource, struct AllocatorObject *allocator, struct RenderResourceContext *rrc);

	/* This is called on the main thread, once the resource data has been loaded. Implement this
	   if you need to register the loaded data in some global structure. */
	void (*bring_in) (void *obj, void *resource);

	/* Implement this to unregister what you registered in bring_in(). */
	void (*bring_out) (void *obj, void *resource);

	/* Allocator used to allocate the data if using default load. Use NULL to use the default
	   allocator. */
	struct AllocatorObject *allocator;

	/* Desired alignment of the loaded resource data into memory if using default load. Use 0 to
	   use default alignment. */
	unsigned int align;

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/*
	Interface to the Stingray ResourceManager. The ResourceManager can be used to query for loaded
	resources as well as to implement custom loaders for custom types.
*/
struct ResourceManagerApi
{
	/* Returns the version number of the resource manager. The version number is changed
	   whenever resources are added or removed. */
	unsigned int (*version)();

	/* Gets a list of loaded resources for the specified type. The function returns the total
	   number of loaded resources of the specified type, and the first names_size of these
	   resources are copied into the names array. You can call the function with zero to size
	   the array. */
	unsigned (*loaded_resources)(const uint64_t type_id, uint64_t *names, unsigned names_size);

	/* Registers a new resource type with the resource manager. The type uses the default load
	   mechanism (i.e. the serialized data will be loaded directly into memory as a data blob,
	   with no additional patching). */
	void (*register_type)(const char *type);

	/* Registers a new resource type with custom load functionality. */
	void (*register_type_with_callbacks)(const char *type, struct RM_ResourceTypeCallbacks * data);

	/* Returns true if there is a loaded resource with the specified type and name. */
	int (*can_get)(const char *type, const char *name);

	/* As can_get(), but uses a hashed type and name instead. */
	int (*can_get_by_id)(uint64_t type_id, uint64_t name_id);

	/* Returns the loaded resource identified by (type, name). This will assert if there is no
	   resource loaded with the specified type and name. */
	void *(*get)(const char *type, const char *name);

	/* As get() but uses a hashed type and name instead. */
	void *(*get_by_id)(uint64_t type_id, uint64_t name_id);

	/* Returns true if the specified resource is online. */
	int(*is_online)(const char *type, const char *name);

	/* As is_online() but uses a hashed type and name instead. */
	int(*is_online_by_id)(uint64_t type_id, uint64_t name_id);

	/* Opens the streamed data belonging to the resource. When you are done with using the data
	   you should destroy it with delete_stream().

	   The data is returned as a FutureInputArchive... this is an input stream that will be
	   ready for reading at some point in the future. */
	struct FutureInputArchive * (*new_open_stream)(struct AllocatorObject * allocator,
		const char * type, const char * name);

	/* As new_open_stream() but uses a hashed type and name instead. */
	struct FutureInputArchive * (*new_open_stream_by_id)(struct AllocatorObject * allocator,
		uint64_t type_id, uint64_t name_id);

	/* Destroys a stream opened by new_open_stream(). */
	void (*delete_stream)(struct FutureInputArchive * fia, struct AllocatorObject * allocator);

	/* Reserved for expansion of the API. */
	void *reserved[30];
};

/* ----------------------------------------------------------------------
	FutureInputArchive
---------------------------------------------------------------------- */

/*
	Interface for FutureInputArchives. A FutureInputArchive is used to represent a file that will
	become readable at some point in the future. A future is used, since accessing the file
	immediately might cause a stall.
*/
struct FutureInputArchiveApi
{
	/* Returns true if the archive is ready to be used, i.e. if new_archive() will succeed without
	   stalling. */
	int (*ready)(struct FutureInputArchive * fia);

	/* Waits for the archive to be ready for usage. Note that this will stall the waiting thread. */
	void (*wait)(struct FutureInputArchive * fia);

	/* Cancels the request for the InputArchive. You can use this if you decide that you are no
	   longer interested in reading from the archive.

	   A FutureInputArchive should always be properly closed, either by calling cancel() on it,
	   or by calling new_archive() to explicitly create an InputArchive from it. */
	void (*cancel)(struct FutureInputArchive * fia);

	/* Creates an InputArchive from the FutureInputArchive. The created archive must be destroyed
	   with delete_archive(). This function will stall if the archive is not ready to be opened. */
	struct InputArchive * (*new_archive)(struct FutureInputArchive * fia,
		struct AllocatorObject * allocator);

	/* Deletes an archive created by new_archive(). You must delete the archive when done with it. */
	void (*delete_archive)(struct InputArchive * fia, struct AllocatorObject * allocator);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	InputArchive
---------------------------------------------------------------------- */

/*
	Interface that represents a stream of data from disk or memory.
*/
struct InputArchiveApi
{
	/* Reads size bytes from the archive into the buffer. */
	void (*read)(struct InputArchive * input_archive, void *buffer, unsigned size);

	/* Sets the read position of the archive to the specified offset. */
	void (*set_position)(struct InputArchive * input_archive, int64_t position);

	/* Returns the size of the archive. */
	int64_t (*size)(struct InputArchive * input_archive);

	/* Provides raw access to the input buffer that feeds the archive. Accessing the input
	   buffer directly is needed if you want to be able to stream data from the archive
	   without stalling. (Just calling read() on a disk archive might stall your thread.) */
	struct InputBuffer * (*buffer)(struct InputArchive * input_archive);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	InputBuffer
---------------------------------------------------------------------- */

/*
	Interface for performing low level operations (such as streaming) on a stream of input data.
*/
struct InputBufferApi
{
	/* The total size of the input buffer data. A never ending buffer will return INT64_MAX. */
	int64_t (*size)(struct InputBuffer * input_buffer);

	/* The number of bytes available to be read directly from the pointer without streaming in
	   more data. */
	unsigned (*available)(struct InputBuffer * input_buffer);

	/* Consumes `bytes` bytes. Note that that many bytes must be available in the buffer. */
	void (*consume)(struct InputBuffer * input_buffer, unsigned bytes);

	/* Ensures that at least the specified number of bytes are available in
	   the buffer. Will flush (stall) to fetch the bytes if necessary. */
	void (*ensure)(struct InputBuffer * input_buffer, unsigned bytes);

	/* Returns a raw pointer to the start of the input stream. You can read available() bytes
	   from the stream and then consume() those bytes to advance the stream pointer. */
	void * (*ptr)(struct InputBuffer * input_buffer);

	/* Returns the current offset of the readhead. */
	int64_t (*position)(struct InputBuffer * input_buffer);

	/* Sets the stream readhead to the specified position. */
	void (*set_position)(struct InputBuffer * input_buffer, int64_t offset);

	/* Sets the size of the "chunks" used to stream in data from disk.
	   Typically an input buffer keeps two chunks in flight, and when you have consumed one chunk
	   fully, a new one is streamed in, in the background. */
	void (*set_read_chunk)(struct InputBuffer * input_buffer, unsigned size);

	/* Fetches more data from the source, ensuring that at least the specified number of
	   bytes are available. This might stall. */
	void (*flush)(struct InputBuffer * input_buffer, unsigned bytes);

	/* Returns true if a flush with a byte size of 0 will succeed without stalling.
	  (I.e. if all pending I/O operations have finished.) */
	int (*can_flush_without_stalling)(struct InputBuffer * input_buffer);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	Logging
---------------------------------------------------------------------- */

/*
	Interface to log messages to the editor console.
*/
struct LoggingApi
{
	/* Logs an informational message */
	void (*info)(const char *system, const char *info);

	/* Logs a warning message. */
	void (*warning)(const char *system, const char *warning);

	/* Logs an error message. */
	void (*error)(const char *system, const char *error);
};

/* ----------------------------------------------------------------------
	RendererInterface
---------------------------------------------------------------------- */

/* Opaque struct representing the render device. On a D3D platform, this will be ID3D11Device. */
struct RI_Device;

/* Enum describing the different resource types used by the renderer. */
enum RI_ResourceType {
	RI_RESOURCE_TEXTURE,
	RI_RESOURCE_RENDER_TARGET,
	RI_RESOURCE_NOT_INITIALIZED = 0x00FFFFFF
};

/* Used to identify a render resource. */
struct RenderResource {
	unsigned handle;
};

#if defined(WINDOWSPC) || defined(XBOXONE) || defined(UWP)
	/* D3D rendering interface. */
	struct ID3D11RenderTargetView;
	struct ID3D11ShaderResourceView;
	struct ID3D11Texture2D;
	struct IDXGISwapChain;

	struct RI_PlatformTexture2d
	{
		struct ID3D11Texture2D          *texture;
		struct ID3D11ShaderResourceView *resource_view;
		struct ID3D11ShaderResourceView *resource_view_srgb;
	};

	struct RI_PlatformRenderTarget
	{
		struct ID3D11RenderTargetView *render_target_view;
	};

	struct RI_PlatformSwapChain
	{
		struct IDXGISwapChain *dxgi_swap_chain;
	};

	struct RI_PlatformWindow
	{
		void *window;
	};
#else
	/* TODO: Implement RI_PlatformRenderTarget for other platforms. */
	struct RI_PlatformRenderTarget { char unused; };

	#if defined(ANDROID)
		/* cf. gl::Context */
		struct RI_Device {
			void* context; /* EGLContext */
			void* display; /* EGLDisplay */
			void* surface; /* EGLSurface */
			void* config;  /* EGLConfig */
		};
	#endif

	#if defined(MACOSX) || defined(IOS) || defined(ANDROID) || defined(WEB) || defined(LINUXPC)
		struct RI_PlatformTexture2d    {
			unsigned int handle; /* binding handle */
			unsigned int format; /* internal pixel format, e.g., GL_DEPTH24_STENCIL8, GL_R16F */
			unsigned int type;   /* channel type info, e.g., GL_UNSIGNED_INT_24_8, GL_UNSIGNED_BYTE */
			unsigned int width;
			unsigned int height;
			unsigned int size;   /* size in bytes used by the texture */
		};
	#else
		/* TODO: Implement Texture2D for other platforms. */
		struct RI_PlatformTexture2d { char unused; };
	#endif

	/* TODO: Implement SwapChain and Window for other platforms. */
	struct RI_PlatformSwapChain    { char unused; };
	struct RI_PlatformWindow       { char unused; };
#endif

/*
	Interface to the Stingray renderer.
*/
struct RenderInterfaceApi
{
	/* Creates a fence for the GPU. */
	int (*create_fence)();

	/* Wait for the GPU to reach the specified fence. */
	void (*wait_for_fence)(int);

	/* Run the specified callback function on the render thread. */
	void (*run_callback)(void(*callback)(void* data), void* user_data, uint32_t user_data_size);

	/* Returns the render device. */
	struct RI_Device* (*device)();

	/* Returns the named global render resource. */
	struct RenderResource* (*global_render_resource)(const char *name);

	/* Returns a texture. */
	struct RI_PlatformTexture2d (*texture_2d)(struct RenderResource *render_resource);

	/* Returns the swap chain. */
	struct RI_PlatformSwapChain (*swap_chain)(unsigned handle);

	/* Returns the render target for the specified swap chain, layer and mip_level. */
	struct RI_PlatformRenderTarget (*render_target)(unsigned handle, int layer, int mip_level);

	/* Returns the window corresponding to the specified handle. */
	struct RI_PlatformWindow (*window)(unsigned handle);

	/* Sets render setting values that are applied to the render configuration  */
	void (*set_render_setting)(const char* name, ConstConfigRootPtr value);

	/* Reserved for expansion of the API. */
	void *reserved[31];
};

/* ----------------------------------------------------------------------
	Unit
---------------------------------------------------------------------- */

/* Enum for the different kinds of physics actors supported. */
enum U_ActorType {
	U_ACTOR_SPHERE =		0,
	U_ACTOR_PLANE =			1,
	U_ACTOR_CAPSULE =		2,
	U_ACTOR_BOX =			3,
	U_ACTOR_CONVEXMESH =	4,
	U_ACTOR_TRIANGLEMESH =	5,
	U_ACTOR_HEIGHTFIELD =	6
};

/* Opaque struct representing a collision filter, that specifies which actors collide with which
	other actors. */
struct CollisionFilter;

/* Represents a triangle mesh. */
struct U_TriangleMesh
{
	const char *indices;
	unsigned num_triangles;
	unsigned index_stride;
	const char *vertices;
	unsigned vertex_stride;
	float transform[16];
};

/* Represents a convex mesh. */
struct U_ConvexMesh
{
	const char *indices;
	unsigned num_polygons;
	unsigned index_stride;
	const char *vertices;
	unsigned vertex_stride;
	float transform[16];
};

/* Represents a height field. */
struct U_HeightField
{
	unsigned num_rows;
	unsigned num_columns;
	float    row_scale;
	float    column_scale;
};

/* Represents a sphere. */
struct U_Sphere
{
	float transform[16];
	float radius;
};

/* Represents a capsule. */
struct U_Capsule
{
	float transform[16];
	float radius;
	float half_height;
};

/* Represents a box. */
struct U_Box
{
	float transform[16];
	float half_extents[3];
};

/* Represents a position in the height field. */
struct U_HeightFieldPos
{
	float pos[3];
};

/* Represents animation clip playback information */
struct U_AnimationPlayingInfo
{
	uint64_t clip_resource_id;
	double time;
	double length;
	uint8_t loop;
};

/* Opaque struct representing a hierarchy of objects in a Unit. */
struct SceneGraph;

/*
	Interface for interacting with units.
*/
struct UnitApi
{
	/* Returns the unit's scene graph. */
	struct SceneGraph * (*scene_graph)(CApiUnit *unit);

	/* Returns a reference to the unit. Unit references are weak pointers that get invalidated when
	   the unit dies. */
	CApiUnitRef (*reference)(CApiUnit * unitobject);

	/* Returns the number of meshes in the unit. */
	int (*num_meshes)(CApiUnit *unit);

	/* Returns the mesh at the specified index. */
	void (*mesh)(CApiUnit *unit, int mesh_index, struct U_TriangleMesh *mesh);

	/* Returns the hashed name of the mesh at the specified index. */
	uint32_t (*mesh_name)(CApiUnit *unit, int mesh_index);

	/* Returns the index of the scene graph node that owns the mesh at the specified index. */
	int (*mesh_node)(CApiUnit *unit, int mesh_index);

	/* True if the specified mesh is visible. */
	int (*is_mesh_visible)(CApiUnit *unit, int mesh_index);

	/* Returns the number of actors in the unit. */
	int (*num_actors)(CApiUnit *unit);

	/* Returns the actor at the specified index. */
	CApiActor* (*actor)(CApiUnit *unit, int index);

	/* True if collisions are enabled for the specified actor. */
	int (*is_collision_enabled)(CApiActor *ao);

	/* True if the specified actor is static. */
	int (*is_static)(CApiActor *ao);

	/* True if the specified actor is kinematic. */
	int (*is_kinematic)(CApiActor * ao);

	/* Returns the number of shapes in the actor. */
	int (*num_shapes)(CApiActor* ao);

	/* Returns the type of the shape at the specified index. */
	int (*shape_type)(CApiActor *ao, int shape_index);

	/* Gets shape data for a sphere shape. Returns false if shape is not a sphere. */
	int (*sphere)(CApiActor *ao, int shape_index, struct U_Sphere *so);

	/* Gets shape data for a capsule shape. Returns false if shape is not a capsule. */
	int (*capsule)(CApiActor *ao, int shape_index, struct U_Capsule *co);

	/* Gets shape data for a box shape. Returns false if shape is not a box. */
	int (*box)(CApiActor *ao, int shape_index, struct U_Box *bo);

	/* Gets shape data for a mesh shape. Returns false if shape is not a mesh. */
	int (*triangle_mesh)(CApiActor *ao, int shape_index, struct U_TriangleMesh *mesh);

	/* Gets shape data for a convex shape. Returns false if shape is not a convex. */
	int (*convex_mesh)(CApiActor *ao, int shape_index, struct U_ConvexMesh *convexmesh);

	/* Returns the number of vertices of the specified polygon in the convex shape. */
	int (*convex_mesh_polygon_num_vertices)(CApiActor *ao, int shape_index, int polygon_index);

	/* Returns the index at which the polygon's vertices start in the convex mesh's
	   vertex buffer. */
	int (*convex_mesh_polygon_base_index)(CApiActor *ao, int shape_index, int polygon_index);

	/* Gets shape data for a height field shape. Returns false if shape is not a height field. */
	int (*height_field)(CApiActor *ao, int shape_index, struct U_HeightField *height_field);

	/* Returns the height field position at the specified coordinates. */
	int (*height_field_position)(CApiActor *ao, int shape_index, float x, float y, struct U_HeightFieldPos *pos);

	/* Returns the unit's mover (character controller). */
	CApiMover* (*mover)(CApiUnit *unit);

	/* Returns the collision filter of the mover. */
	struct CollisionFilter* (*collision_filter)(CApiMover *mo);

	/* Returns the hash of the unit's resource name. */
	uint64_t (*unit_resource_name)(CApiUnit *unit);

	/* Gets the value of the unit animation curve for the specified object and parameter.
	   Returns true if the curve value was successfully fetched. */
	uint8_t (*get_curve_value)(CApiUnit *unit, uint32_t object, uint32_t parameter, unsigned count, float* floats);

	/* Query number of playing animation clips and fill in playback details. */
	uint32_t (*get_playing_animation_infos)(CApiUnit *unit, uint32_t layer_id, struct U_AnimationPlayingInfo *playing_infos, uint32_t maximum);

	/* The world that the unit lives in. */
	CApiWorld* (*world)(CApiUnit *unit);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/*
	Interface for working with unit references. Unit references are weak pointers that get
	invalidated when the unit is destroyed.
*/
struct UnitReferenceApi
{
	/* Dereferences the reference into a unit pointer. Returns NULL if the unit has been
	   destroyed. */
	CApiUnit * (*dereference)(CApiUnitRef ref);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	SceneGraph
---------------------------------------------------------------------- */

/* Opaque struct that represents the "dirty" state of nodes in a unit's scene graph. I.e. a bit
	flag for each node that is dirty and needs its transform updated. */
struct SceneFlags;

/*
	Interface for manipulating scene graphs (i.e., node hierarchies inside units).
*/
struct SceneGraphApi
{
	/* Returns the world matrix of the node in the scene graph with specified index. The matrix
	   is returned as an array of 16 floats. */
	const float * (*world)(struct SceneGraph * scene_graph, int index);

	/* Returns the local transform of the node with the specified index. */
	const CApiLocalTransform * (*local)(struct SceneGraph *scene_graph, int index);

	/* Returns the scene graph's render handle to be used with the RenderSceneGraphApi. */
	uint32_t (*render_handle)(struct SceneGraph *scene_graph);

	/* Transforms the scene graph using the specified node as root. This updates the world
	   transforms of all objects based on their parent's transform and their local transforms. */
	void (*transform_with_root)(struct SceneGraph *scene_graph, int index, ConstMatrix4x4Ptr root);

	/* Unlinks the node at the index from its current parent. */
	void (*unlink_internal)(struct SceneGraph *scene_graph, int index);

	/* Relinks a node back to its parent. */
	void (*relink_internal)(struct SceneGraph *scene_graph, int index);

	/* Returns the total number of nodes in the scene graph. */
	uint32_t (*num_nodes)(struct SceneGraph *scene_graph);

	/* Returns the index of the parent node to the node at the specified index. If the node
	   doesn't have a parent, this function returns -1. */
	int (*parent)(struct SceneGraph *scene_graph, int index);

	/* Returns true if the node with the specified index is a root (i.e., does not have a parent
		node). */
	uint8_t (*is_root)(struct SceneGraph * scene_graph, int index);

	/* Returns the 32 bit hash of the node's name. */
	uint32_t (*name)(struct SceneGraph *scene_graph, int index);

	/* Returns a pointer to an array with the hashes of all the node names in the scene graph. */
	uint32_t * (*names_array_pointer)(struct SceneGraph *scene_graph);

	/* Returns the array of dirty flags. This is a bit array with the bit set for each node that
	   has a local transform change that has not yet been reflected to its world transform. This
	   array can be(useful when defining a post animation callback that changes local node transforms. */
	struct SceneFlags * (*dirty_array_pointer)(struct SceneGraph *scene_graph);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	Application
---------------------------------------------------------------------- */

/* Opaque struct that represents the command-line options that were passed to the application at
	launch. */
struct ApplicationOptions;

/* Abstract struct that can be cast to either ANativeActivity or UIApplication based on the
	platform. */
struct AP_PlatformActivity;

/* Specifies whether callbacks should be called before the activity happens or after it happens. */
enum AP_PlatformCallbackOrder
{
	AP_PRE_ACTIVITY,
	AP_POST_ACTIVITY
};

/* Callbacks for Android activity events. See Android documentation. */
struct AndroidActivityCallbacks
{
	void (*start)(struct AP_PlatformActivity*);
	void (*resume)(struct AP_PlatformActivity*);
	void * (*save_instance_state)(struct AP_PlatformActivity*, size_t*);
	void (*pause)(struct AP_PlatformActivity*);
	void (*stop)(struct AP_PlatformActivity*);
	void (*destroy)(struct AP_PlatformActivity*);
	void (*window_focus_changed)(struct AP_PlatformActivity*, int);
	void (*native_window_created)(struct AP_PlatformActivity*, void*);
	void (*native_window_resized)(struct AP_PlatformActivity*, void*);
	void (*native_window_redraw_needed)(struct AP_PlatformActivity*, void*);
	void (*native_window_destroyed)(struct AP_PlatformActivity*, void*);
	void (*input_queue_created)(struct AP_PlatformActivity*, void*);
	void (*input_queue_destroyed)(struct AP_PlatformActivity*, void*);
	void (*content_rect_changed)(struct AP_PlatformActivity*, const void*);
	void (*configuration_changed)(struct AP_PlatformActivity*);
	void (*low_memory)(struct AP_PlatformActivity*);
};

/* Callbacks for iOS activity events. See iOS documentation. */
struct IOSActivityCallbacks
{
	void (*did_finish_launching)(struct AP_PlatformActivity*);
	void (*will_enter_foreground)(struct AP_PlatformActivity*);
	void (*will_terminate)(struct AP_PlatformActivity*);
	void (*did_receive_memory_warning)(struct AP_PlatformActivity*);
	void (*will_resign_active)(struct AP_PlatformActivity*);
	void (*did_enter_background)(struct AP_PlatformActivity*);
	void (*did_become_active)(struct AP_PlatformActivity*);
};

/* Abstract struct representing platform activity callbacks that should be either an
	AndroidActivityCallbacks or an IOSActivityCallbacks. */
struct PlatformActivityCallbacks;

/* Function type for receiving console commands. client_id is the ID of the console client
	instigating the command. ConstConfigRootPtr is a ConstConfig representation of the console
	command's JSON data. data and data_length is any binary data that was sent with the command. */
typedef void (*AP_ReceiverFunction)(void *user_data, int client_id, ConstConfigRootPtr dv,
	const char *data, uint32_t data_length);

/* Wraps a console command receiver callback with a user_data value that will be passed to the
	callback. */
struct AP_ReceiverUserDataWrapper
{
	void * user_data;
	AP_ReceiverFunction function;
};

/*
	Interface for manipulating the application.
*/
struct ApplicationApi
{
	/* Returns the command-line options that were passed to the application at launch. */
	const struct ApplicationOptions * (*options)();

	/* Returns a representation of the settings.ini file used with the application. The settings
	   are returned as a pointer to a ConstConfigRoot item and can be parsed using the ConstConfig
	   API in the plugin foundation. */
	const void * (*settings)();

	/* Returns the activity interface for native lifecycle handling. */
	struct AP_PlatformActivity * (*platform_activity)();

	/* Register platform activity callbacks to be called on platform activity events. */
	void (*register_platform_callbacks)(enum AP_PlatformCallbackOrder,
		const struct PlatformActivityCallbacks*);

	/* Unregisters callbacks registered with register_platform_callbacks(). */
	void (*unregister_platform_callbacks)(enum AP_PlatformCallbackOrder,
		const struct PlatformActivityCallbacks*);

	/* Returns the number of worlds managed by the application. */
	int (*num_worlds)();

	/* Returns the world at the specified index. */
	CApiWorld * (*world)(int index);

	/* Returns a string identifying the Stingray version. */
	const char * (*product_version)();

	/* Hooks a receiver function for console connection commands. This allows you to extend the
	   console interface with your own commands. */
	void (*hook_console_receiver)(const char *type, struct AP_ReceiverUserDataWrapper *user_wrapper);

	/* Unhooks a receiver hooked with hook_console_receiver(). */
	void (*unhook_console_receiver)(const char *type);

	/* Can be used in console receivers to get the id of the console connection that originated
	   the command. */
	int (*current_client_id)();

	/* Returns the holographic space created early in the app lifecycle when on the Hololens platform.
	   Null otherwise. TODO: Adding a plugin hook early enough in the app lifecycle (pre-window activation)
	   would alleviate the need for this API member. */
	void * (*holographic_space)();

	/* Sends data over a console connection. The data sent can be a combination of textual data
	   (JSON) and a binary payload. If sync is true, the send is synchronized. If client_id is
	   not -1, then the message is only sent to that particular console client instead of
	   broadcast to everybody. */
	void (*console_send_with_binary_data)(const char *text, uint32_t text_len, const char *data,
		uint32_t data_len, uint8_t sync, int client_id);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	ApplicationOptions
---------------------------------------------------------------------- */

/*
	Interface to read the command options used when launching the application.
*/
struct ApplicationOptionsApi
{
	/* Returns the bundle directory if the engine was launched in bundle mode. */
	const char * (*bundle_directory)(const struct ApplicationOptions * application_options);

	/* Returns the data directory if the engine was launched in data directory mode. */
	const char * (*data_directory)(const struct ApplicationOptions * application_options);

	/* Returns true if rendering is enabled. */
	int (*is_rendering_enabled)(const struct ApplicationOptions * application_options);

	/* Reserved for expansion of the API. */
	void *reserved[31];
};

/* ----------------------------------------------------------------------
	ErrorContext
---------------------------------------------------------------------- */

/*
	Allows plugins to use the error context functionality on custom threads created by
	the plugin.
*/
struct ErrorContextApi
{
	/* Creates a thread error context stack for the current thread. */
	void (*make_thread_error_context_stack)(struct AllocatorObject *allocator);

	/* Deletes the thread error context stack for the current thread. */
	void (*delete_thread_error_context_stack)(struct AllocatorObject *allocator);

	/* Returns true if the current thread has en error context stack and false otherwise. */
	int (*has_thread_error_context_stack)();

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	Raycast
---------------------------------------------------------------------- */

/*
	Interface for performing raycasts.
*/
struct RaycastApi
{
	/* Casts a ray into the world, from the origin in the specified direction. Only actors matching
	   the collision filter are considered. If a hit is found, the function returns true and sets
	   the hit position and normal in the out parameters. */
	int (*find_first_collision)(
		CApiWorld *world,
		float ray_origin_x, float ray_origin_y, float ray_origin_z,
		float ray_direction_x, float ray_direction_y, float ray_direction_z,
		float ray_length,
		struct CollisionFilter *collision_filter,
		float *hit_position_x, float *hit_position_y, float *hit_position_z,
		float *hit_normal_x, float *hit_normal_y, float *hit_normal_z);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	FileSystem
---------------------------------------------------------------------- */

/* Opaque struct representing a file system. */
struct FileSystem;

/*
	Interface for accessing a file system.
*/
struct FileSystemApi
{
	/* Returns true if a file with the specified name exists in the file system. */
	int (*exists)(struct FileSystem *filesystem, const char *filename);

	/* Creates a new disk file system with the specified directory as its root. You can use
	   the empty string for the directory if you want a file system that represents the entire
	   disk. */
	struct FileSystem * (*create)(const char *directory);

	/* Destroys a file syste created by create(). */
	void (*destroy)(struct FileSystem *filesystem);

	/* Returns true if the specified path is a directory, false if it isn't or if there
	  was an error. If there was an error, the error message is returned in the error
	  parameter. */
	int (*is_directory)(struct FileSystem *filesystem, const char *file, const char **error);

	/* Creates a directory at the specified path. Returns NULL if successful and an
	   error message otherwise. */
	const char * (*make_directory)(struct FileSystem *filesystem, const char *file);

	/* Reads file, parses it into ConstConfig */
	ConstConfigRootPtr (*parse_sjson)(struct FileSystem *filesystem, const char *file, struct AllocatorObject *allocator, const char **error);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	PluginManager
---------------------------------------------------------------------- */

/*
	Interface for manipulating the plugin system.
*/
struct PluginManagerApi
{
	/* On-demand loads the plugin at the specified path.  */
	void (*load_relative_plugin)(const char *plugin_relative_path);

	/* Used to enumerate services exposed by plugins. Call it with an API ID and NULL to retrieve
	   a pointer to the first interface that implements a certain API. Repeat the call with the
	   previously returned pointer to continue enumerating implementations. The function will
	   return NULL when all interfaces have been enumerated.

	   Note that this function will only enumerate services implemented in plugins, not the ones
	   implemented in the engine. */
	void *(*get_next_plugin_api)(unsigned api_id, void *prev_api);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	World
---------------------------------------------------------------------- */

/* Opaque struct representing a scope for drawing lines. */
struct LineObjectDrawer;

/* Callback to be called after animations have been evaluated. */
typedef void (*PostAnimationCallback)(CApiWorld * world_object, float dt);

/*
	Interface for accessing the world.
*/
struct WorldApi
{
	/* Returns a LineObjectDrawer that can be used to draw debug lines into the world. */
	struct LineObjectDrawer * (*line_object_drawer)(CApiWorld * world);

	/* Registers a callback that will run after animations (forward kinematics) have been run.
	   This can be used to implement IK and other animation controllers. */
	void (*register_post_animation_callback)(CApiWorld * world, PostAnimationCallback function);

	/* Unregisters a callback registered with register_post_animation_callback(). */
	void (*unregister_post_animation_callback)(CApiWorld * world, PostAnimationCallback function);

	/* Finds all the instances of the named unit resource in the level. The unit resource is
	   identified by a 64 bit hash.

	   The function returns the total number of units of the specified type found in the level
	   and the first units_size of these are copied into the array. */
	unsigned (*find_units_by_resource_name)(CApiWorld *world, uint64_t resource_name,
		CApiUnit **units, unsigned units_size);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	LineObjectDrawer
---------------------------------------------------------------------- */

/* Opaque struct that represents a collection of drawn lines. */
struct LineObject;

/*
	Interface for drawing debug lines.
*/
struct LineObjectDrawerApi
{
	/* Creates a new line object for drawing a number of lines. */
	struct LineObject *(*new_line_object)(struct LineObjectDrawer * drawer);

	/* Frees a line object created by new_line_object(). */
	void (*release_line_object)(struct LineObjectDrawer * drawer, struct LineObject *lo);

	/* Dispatches the lines drawn into the specified line object to the renderer for rendering. */
	void (*dispatch)(struct LineObjectDrawer * drawer, struct StateReflectionStream *srs,
		struct LineObject *lo);

	/* Clears the lines from the line object. */
	void (*reset)(struct LineObject * lo);

	/* Adds a number of lines to the line objects. The colors array encodes the color of each line
	   as an ARGB unsigned. The line_starts and line_ends array encode interleaved x, y, z coordinates
	   for the start points and end points of each line respectively. n is the total number of lines
	   added. */
	void (*add_lines)(struct LineObject * lo, unsigned * colors, float * line_starts, float * line_ends, unsigned n);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	Profiler
---------------------------------------------------------------------- */

/*
	Interface to the Stingray profiler.
*/
struct ProfilerApi
{
	/* Starts a new profiler scope with the specified name. Each call to profile_start() should
	   be matched by a corresponding call to profile_stop(). */
	void (*profile_start)(const char *name);

	/* Ends a profile scope started by profile_start(). */
	void (*profile_stop)();

	/* Function for creating a profiler for a specific thread.
		Must be called on the thread that the profiler should be created for. */
	void (*make_thread_profiler)(struct AllocatorObject *allocator);

	/* Function for deleting a profiler for a specific thread.
		Must be called on the thread that the profiler should be deleted for. */
	void (*delete_thread_profiler)(struct AllocatorObject *allocator);

	/* Checks if the current thread already has a thread profiler. */
	int (*has_thread_profiler)();

	/* Reserved for expansion of the API. */
	void *reserved[29];
};

/* ----------------------------------------------------------------------
	Error
---------------------------------------------------------------------- */

/*
	Interface for reporting errors.
*/
struct ErrorApi
{
	/* printf() function for generating error messages. The messages will be generated into a ring
	   buffer that eventually gets recycled. */
	const char *(*eprintf)(const char *msg, ...);

	/* Reports a crash with the specified error message. */
	void (*report_crash)(const char *msg);

	/* Reports an assert() failure at the specified line and file. */
	void (*report_assert_failure)(int line, const char *file, const char *assert_test, const char *msg);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	RenderBuffer
---------------------------------------------------------------------- */

/* Enum for all the texture compression formats supported by the engine. This gets encoded into the
	buffer_format (uint32_t) when the user creates a format using
	RenderBufferApi::compressed_format(). */
typedef enum
{
	/* https://en.wikipedia.org/wiki/S3_Texture_Compression */
	RB_BLOCK_COMPRESSED_1 = 0x0,	/* BC1 */
	RB_BLOCK_COMPRESSED_2,			/* BC2 */
	RB_BLOCK_COMPRESSED_3,			/* BC3 */
	RB_BLOCK_COMPRESSED_4,			/* BC4 */
	RB_BLOCK_COMPRESSED_5,			/* BC5 */
	RB_BLOCK_COMPRESSED_6,			/* BC6 */
	RB_BLOCK_COMPRESSED_7,			/* BC7 */
	/* https://en.wikipedia.org/wiki/PVRTC */
	RB_PVR_RGB_2BPP		  = 0x100,	/* PVR RGB  2BPP */
	RB_PVR_RGBA_2BPP,				/* PVR RGBA 2BPP */
	RB_PVR_RGB_4BPP,				/* PVR RGB  4BPP */
	RB_PVR_RGBA_4BPP,				/* PVR RGBA 4BPP */
	/* https://en.wikipedia.org/wiki/Ericsson_Texture_Compression */
	RB_ETC2_RGB8		  = 0x200,	/* ETC2 RGB8 */
	RB_ETC2_RGB8A1,					/* ETC2 RGB8A1 */
	RB_ETC2_RGBA8,					/* ETC2 RGBA8 */
	RB_ETC2_R11,					/* ETC2 R11 */
	RB_ETC2_RG11					/* ETC2 RG11 */
} RB_CompressedFormat;

/* Buffer component type. */
typedef enum
{
	RB_FLOAT_COMPONENT = 0,
	RB_INTEGER_COMPONENT = 1
} RB_ComponentType;

/* RenderBuffer Descriptors ---------------------------------------------*/

/* Vertex channel semantic names. */
typedef enum
{
	RB_POSITION_SEMANTIC,
	RB_NORMAL_SEMANTIC,
	RB_TANGENT_SEMANTIC,
	RB_BINORMAL_SEMANTIC,
	RB_TEXCOORD_SEMANTIC,
	RB_COLOR_SEMANTIC,
	RB_BLEND_INDICES_SEMANTIC,
	RB_BLEND_WEIGHTS_SEMANTIC,
	RB_UNKNOWN_SEMANTIC,
	RB_SEMANTIC_COUNT = RB_UNKNOWN_SEMANTIC
} RB_VertexSemantic;

/* Describes a vertex channel inside a vertex buffe.r */
struct RB_VertexChannel
{
	uint32_t format;				/* Created using RenderBufferApi::format(). */
	uint8_t semantic;				/* Semantic name from RB_VertexSemantic. */
	uint8_t vb_index;				/* Vertex buffer index. */
	uint8_t set;					/* Semantic set (TEXCOORD0, TEXCOORD1, etc..). */
	uint8_t instance;				/* true if vertex channel contains per instance data. */
};

/* Describes a vertex format as a collection of vertex channels. */
struct RB_VertexDescription
{
	struct RB_VertexChannel channels[16];
	uint32_t n_channels;
};

typedef enum
{
	RB_VERTEX_DESCRIPTION			/* View of RB_VertexDescription. */
} RB_Description;

/* RenderBuffer Views -----------------------------------------*/

struct RB_VertexBufferView
{
	uint32_t stride;				/* Per vertex stride in bytes. */
	uint32_t reserved[7];			/* Reserved for future use - must be zero. */
};

struct RB_IndexBufferView
{
	uint32_t stride;				/* Per index stride in bytes (must be 2 or 4). */
	uint32_t reserved[7];			/* Reserved for future use - must be zero. */
};

struct RB_RawBufferView
{
	uint32_t format;				/* Format descriptor. */
	uint32_t reserved[7];			/* Reserved for future use - Must be zero. */
};

/* Enum for the supported texture types. */
typedef enum
{
	RB_TEXTURE_TYPE_2D = 0,
	RB_TEXTURE_TYPE_CUBE = 1,
	RB_TEXTURE_TYPE_3D = 2
} RB_TextureBufferType;

/* View into a texture buffer. */
struct RB_TextureBufferView
{
	uint32_t format;				/* Format of texture buffer. */
	uint32_t type;					/* Type of texture, should be any of the available types in RB_TextureBufferType. */
	uint32_t width;					/* Width of texture. */
	uint32_t height;				/* Height of texture. */
	uint32_t depth;					/* Depth of texture (Only used if type == RB_TEXTURE_TYPE_3D). */
	uint32_t slices;				/* Number of slices (1 for regular textures, >1 for texture arrays). */
	uint32_t mip_levels;			/* Number of mip levels in buffer. */
	uint32_t reserved[7];			/* Reserved for future use - must be zero. */
};

/* Enum enumerating view types. */
typedef enum
{
	RB_VERTEX_BUFFER_VIEW,			/* View of RB_VertexBufferView */
	RB_INDEX_BUFFER_VIEW,			/* View of RB_IndexBufferView */
	RB_RAW_BUFFER_VIEW,				/* View of RB_RawBufferView */
	RB_TEXTURE_BUFFER_VIEW			/* View of RB_TextureBufferView */
} RB_View;

/* RenderBuffer API----------------------------------------------*/

/* Represents updatability of a buffer. */
typedef enum
{
	/* The buffer is immutable. The content of the buffer must be passed in create_buffer() and
	   cannot change after that. */
	RB_VALIDITY_STATIC,

	/* The content of the buffer can be updated with update_buffer(). */
	RB_VALIDITY_UPDATABLE
} RB_Validity;

struct RenderBufferApi
{
	/* Creates a format descriptor describing a piece of data in a buffer.
		type = RB_FLOAT_COMPONENT or RB_INTEGER_COMPONENT
		signed_bool = true if component should be treated as signed
		normalize_bool = true if component should be as a normalized value when read in a shader
		bit_depth_ = number of bits per x,y,z,w component
	*/
	uint32_t (*format)(RB_ComponentType type, uint8_t signed_bool, uint8_t normalize_bool, uint8_t bit_depth_x, uint8_t bit_depth_y, uint8_t bit_depth_z, uint8_t bit_depth_w);

	/* Creates a format descriptor describing a compressed buffer. */
	uint32_t (*compressed_format)(RB_CompressedFormat compression);

	/* Returns true if format is a compressed format. */
	uint8_t (*is_compressed)(uint32_t format);

	/* Returns total number of bits used by the format.*/
	uint32_t (*num_bits)(uint32_t format);

	/* Returns the number of components in the format. */
	uint32_t (*num_components)(uint32_t format);

	/* Returns the component type for the format */
	RB_ComponentType (*component_type)(uint32_t format);

	/* Creates a descriptor object of the specified type and returns a handle to it.
	   desc should be an appropriate RB_*Description object. */
	uint32_t (*create_description)(RB_Description view, const void *desc);

	/* Updates the specified descriptor object. */
	void (*update_description)(uint32_t handle, const void *desc);

	/* Destroys a descriptor object created by create_description(). */
	void (*destroy_description)(uint32_t handle);

	/* Creates a buffer with the specified parameters and returns a handle to it.
	   view_data should be an appropriate RB_*View object and data should be the raw buffer data. */
	uint32_t (*create_buffer)(uint32_t size, RB_Validity validity, RB_View view, const void *view_data, const void *data);

	/* Updates the buffer with the specified content. */
	void (*update_buffer)(uint32_t handle, uint32_t size, const void *data);

	/* Destroys a buffer created by create_buffer(). */
	void (*destroy_buffer)(uint32_t handle);

	/* Translates a handle to a RenderResource that can be piped to MeshObjectApi::add_resource(),
	   remove_resource() as well as the Lua interface Material.set_resource(). */
	struct RenderResource* (*lookup_resource)(uint32_t handle);

	/* Overrides a resource with another resource. */
	void (*resource_override)(struct RenderResource *resource_to_override, struct RenderResource *resource);

	/* Releases the override done to the resource.*/
	void (*release_resource_override)(struct RenderResource *overriden_resource);

	/* Partial update of a buffer, offset and size in bytes. Partial updates are not allowed to grow a buffer, use update_buffer if you need to resize the buffer. */
	void(*partial_update_buffer)(uint32_t handle, uint32_t offset, uint32_t size, const void *data);

	/* Partial update of a texture buffer, offset[] and size[] are in pixels. Partial updates are not allowed to grow a buffer, use update_buffer if you need to resize the buffer. */
	/* array_index, slice_index and mip_index describes which surface of the image to update. for now array_index must always be 0. */
	/* Valid ranges for slice_index and mip_index depends on RB_TextureBufferView used when creating the texture. */
	void(*partial_update_texture)(uint32_t handle, uint32_t array_index, uint32_t slice_index, uint32_t mip_index, uint32_t offset[3], uint32_t size[3], const void *data);

	/* Updates the specified descriptor object. */
	void(*update_description_from_resource)(struct RenderResource *resource, const void *desc);

	/* Updates the buffer with the specified content. */
	void(*update_buffer_from_resource)(struct RenderResource *resource, uint32_t size, const void *data);

	/* Reserved for expansion of the API. */
	void *reserved[26];
};

/* ----------------------------------------------------------------------
	MeshObject
---------------------------------------------------------------------- */

/* Describes the primitive type for a render batch. */
typedef enum { MO_TRIANGLE_LIST, MO_LINE_LIST } MO_PrimitiveType;

/* Describes a render batch in a mesh. */
struct MO_BatchInfo
{
	MO_PrimitiveType primitive_type;		/* Primitive type.e */
	uint32_t material_index;				/* Index into material array set by MeshObjectApi::set_materials() function. */
	uint32_t vertex_offset;					/* Offset to first vertex to read from vertex buffer. (If set when indexed this value is added to the index fetched from the index buffer before fetching the vertex.) */
	uint32_t primitives;					/* Number of primitives to draw. */
	uint32_t index_offset;					/* Offset to the first index to read from the index buffer (only valid when batch is indexed). */
	uint32_t vertices;						/* Number of vertices in batch (only valid if batch is non indexed). */
	uint32_t instances;						/* Number of instances of this batch to draw (1 equals no instancing). */
};

/* Describes a piece of mesh geometry for rendering. */
struct MO_Geometry
{
	void *vertices[8];						/* Holds 0-8 different vertex buffers, contents described by vertex_channels[]. If mesh references more than 8 vertex buffers MeshObjectApi will generate an error. */
	uint32_t vertex_stride[8];				/* Holds 0-8 strides, one for each buffer in vertices[]. */
	uint32_t num_vertices;					/* Total number of vertices. */
	struct RB_VertexDescription vertex_description;/* Vertex description. */

	void *indices;							/* Pointer to index list. */
	uint32_t index_stride;					/* Stride of index list (2 or 4). */
	uint32_t num_indices;					/* Total number of indices. */
};

/* Describes a piece of mesh geometry for rendering. */
struct MO_MeshGeometry
{
	struct RenderResource *vertex_stream;
	struct RenderResource *vertex_description;
	struct RenderResource *index_stream;
};

/* Culling flags for meshes. */
typedef enum
{
	MO_VIEWPORT_VISIBLE_FLAG = 0x1,		/* Mesh is part of regular rendering */
	MO_SHADOW_CASTER_FLAG = 0x2,		/* Mesh is part of shadow rendering */
	MO_DISABLE_CULLING_FLAG = 0x4		/* Mesh always passes culling, i.e its bounding volume state is ignored. Note: might significantly impact performance */
} MO_Flags;

/* A context in which the mesh is either visible or not. */
typedef enum
{
	MO_VIEWPORT_CONTEXT,				/* Visibility context for regular rendering */
	MO_SHADOW_CASTER_CONTEXT,			/* Visibility context for shadow casting */
	MO_ALL_CONTEXTS						/* Visibility context for both regular rendering and shadow casting */
} MO_VisibilityContexts;

struct MeshObjectApi
{
	/* Tries to retrieve the geometry of an existing mesh and if successful returns it in
	   MO_Geometry (this will only give valid results when a representation of the geometry exist
	   on the CPU side). */
	uint8_t (*read_geometry)(CApiUnit *unit, uint32_t mesh_name, struct MO_Geometry *geometry);

	/* Creates a new mesh object linked to the node referenced by node_name within the Unit
	   referenced by unit. The mesh_name is given to the new MeshObject and can be used to
	   retrieve the object from the Unit interface. flags is a combination of MO_Flags */
	uint32_t (*create)(CApiUnit *unit, uint32_t node_name, uint32_t mesh_name, uint32_t flags);

	/* Lookup an existing mesh object by name */
	uint32_t (*lookup)(CApiUnit *unit, uint32_t mesh_name);

	/* Destroy a mesh object created using create() or lookup(), for meshes looked up using
	   lookup() this just releases the plugin handle. */
	void (*destroy)(uint32_t handle);

	/* Assigns an array of materials to the mesh. material_resources is an array of material
	  resources retrieved using ResourceManagerApi::get() */
	void (*set_materials)(uint32_t handle, uint32_t num_materials, void **material_resources);

	/* Returns the number of materials assigned to the mesh */
	uint32_t (*num_materials)(uint32_t handle);

	/* Returns a pointer to the material instance at the specified index. */
	void * (*material)(uint32_t handle, uint32_t material_index);

	/* Sets batch/drawcall information of the mesh */
	void (*set_batch_info)(uint32_t handle, uint32_t num_infos, struct MO_BatchInfo *batch_infos);

	/* Adds resources such as vertex buffers, index buffers and vertex declarations created through
	   the RenderBufferApi or piped down from Lua. */
	void (*add_resource)(uint32_t handle, struct RenderResource *r);

	/* Removes a resource added with add_resource(). */
	void (*remove_resource)(uint32_t handle, struct RenderResource *r);

	/* Clears any already assigned resources from a mesh */
	void (*clear_resources)(uint32_t handle);

	/* Sets min & max bounds in mesh local coordinates to be used for culling. */
	void (*set_bounding_box)(uint32_t handle, float min[3], float max[3]);

	/* Sets visibility of the mesh for a specific MO_VisibilityContext */
	void (*set_visibility)(uint32_t handle, uint32_t visibility_context, uint8_t visibility_bool);

	/* Returns the visibility of the mesh in the specified context. */
	uint8_t (*visibility)(uint32_t handle, uint32_t visibility_context);

	/* Sets the culling MO_Flags for object (will overrride the flags passed in create()). */
	void (*set_flags)(uint32_t handle, uint32_t flags);

	/* Returns the culling flags of the object. */
	uint32_t (*flags)(uint32_t handle);

	/* Creates a new empty mesh object. A scene graph must be associated to it and it must be dispatched
	   to the render thread through a render interface before use with the mesh api. (this is currently
	   used for the mesh component api) */
	uint32_t (*create_mesh)(WorldPtr world, uint32_t mesh_name, uint32_t flags);

	/* Lookup an existing mesh object by its handle */
	MeshPtr(*lookup_mesh)(uint32_t handle);

	/* Tries to retrieve the mesh geometry of an existing mesh and if successful returns it in
	   MO_MeshGeometry. */
	uint8_t (*read_mesh_geometry)(void *unit_resource, uint32_t mesh_name, struct MO_MeshGeometry *geometry);

	/* Reserved for expansion of the API. */
	void *reserved[29];
};

/* ----------------------------------------------------------------------
	SoundStreamSourceApi
---------------------------------------------------------------------- */

#pragma pack(push, 1)

/* Represents the format for sound data. */
struct WaveFormat
{
	unsigned short      format_tag;					/* Tag specifying the format (e.g. WAVE_FORMAT_PCM). */
	unsigned short      num_channels;				/* Number of sound channels (e.g. 2). */
	unsigned			samples_per_second;			/* Samples per second (e.g. 44100). */
	unsigned			average_bytes_per_second;	/* Not used. */
	unsigned short		block_align;				/* For MP3 files, samples per frame. */
	unsigned short      bits_per_sample;			/* Bits per sample (e.g. 16). */
	unsigned short      size;						/* Number of extra bytes of header data. */
};

#pragma pack(pop)

/* Sound debug information. */
struct SoundData
{
	unsigned id;	 		/* IdString32 equivalent */
	char debug_name[32];
};

/* Header for a piece of sound data. */
struct SoundHeader
{
	unsigned			offset;			/* Offset of sample data in the file */
	unsigned			size;			/* Size of sample data */
	unsigned			num_samples;	/* Total number of samples (when unpacked) */
	struct SoundData	sound_data;		/* Debug information */
};

/* Opaque struct representing a compiled piece of sound. */
struct SoundResource;

/* The result of streaming sound data. Contains the next chunk of streamed data. The
	is_finished flag is set to true if this is the last chunk of sound data in the stream. */
struct GetNextChunkResult
{
	struct SoundResource * data;
	int is_finished;
};

/* Opaque struct representing a sound source for streaming sounds. */
struct SoundStreamSource;

/*
	Interface for streaming sounds.
*/
struct SoundStreamSourceApi
{
	/* Get the next chunk of streaming data from the stream source. */
	struct GetNextChunkResult (*get_next_chunk)(struct SoundStreamSource * ss);

	/* Gets the sound resource for the stream source. */
	struct SoundResource * (*get_resource)(struct SoundStreamSource * ss);

	/* Gets the sound header for the specified sound resource. */
	struct SoundHeader (*resource_header)(struct SoundResource * sr);

	/* Gets the sound format for the specified sound resource. */
	struct WaveFormat (*resource_format)(struct SoundResource * sr);
};

/* ----------------------------------------------------------------------
	MaterialApi
---------------------------------------------------------------------- */

/*
	Interface for manipulating materials.
*/
struct MaterialApi
{
	/* Sets a number of resources to be used by the material. The resources are identified
	   by their hashed names. */
	void (*set_resources)(void *material, uint32_t num_resources, const uint32_t *resource_names,
		const struct RenderResource **resources);

	/* Sets a number of constants for the material. */
	void (*set_constants)(void *material, uint32_t num_constants, const uint32_t *constant_names,
		const uint32_t *strides, const uint32_t *sizes, const void **constants);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	RenderSceneGraphApi
---------------------------------------------------------------------- */

/*
	Interface for accessing the render thread copy of the scene graph. These functions should
	only be called on the render thread.
*/
struct RenderSceneGraphApi
{
	/* Returns the world matrix of the specified scene graph node. */
	ConstMatrix4x4Ptr (*world)(uint32_t render_handle, CApiWorld *world, unsigned index);

	/* Sets the world matrix of the specified scene graph node. */
	void (*set_world)(uint32_t render_handle, CApiWorld *world, unsigned index, ConstMatrix4x4Ptr m);

	/* Sets the world matrix of the specified scene graph node and transform its children
	   accordingly */
	void (*transform_hierarchy)(uint32_t render_handle, CApiWorld *world, const struct SceneGraph *graph, unsigned index, ConstMatrix4x4Ptr m);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	ThreadApi
---------------------------------------------------------------------- */

/* Defines for thread priorities. */
#define PLUGIN_THREAD_PRIORITY_IDLE -15
#define PLUGIN_THREAD_PRIORITY_LOWEST -2
#define PLUGIN_THREAD_PRIORITY_BELOW_NORMAL -1
#define PLUGIN_THREAD_PRIORITY_NORMAL 0
#define PLUGIN_THREAD_PRIORITY_ABOVE_NORMAL 1
#define PLUGIN_THREAD_PRIORITY_HIGHEST 2
#define PLUGIN_THREAD_PRIORITY_TIME_CRITICAL 15

/* ID for identifying a particular thread. */
typedef void* ThreadID;

/* Thread entry point callback function. */
typedef void (*ThreadEntry)(void* user_data);

/* Opaque struct representing an event. */
struct ThreadEvent;

/* Opaque struct representing a critical section. */
struct ThreadCriticalSection;

/*
	Interface for accessing threading functionality.
*/
struct ThreadApi
{
	/* Creates a new thread and returns its ID. The user_data is passed to the thread entry point. */
	ThreadID (*create_thread)(const char *thread_name, ThreadEntry entry, void *user_data, int priority);

	/* Returns true if the thread is alive. */
	int (*is_thread_alive)(ThreadID thread_id);

	/* Returns the name of the specified thread. */
	const char* (*thread_name)(ThreadID thread_id);

	/* Waits until the thread has finished. */
	void (*wait_for_thread)(ThreadID thread_id);

	/* Creates an event for thread signaling. If manual_reset is false, the event will be
	   auto-reset after being triggered. initial_state specifies the initial state of the
	   event (set or not). */
	struct ThreadEvent* (*create_event)(struct AllocatorObject *allocator, int manual_reset, int initial_state, const char *debug_name);

	/* Destroys an event created by create_event(). */
	void (*destroy_event)(struct ThreadEvent* evt, struct AllocatorObject *allocator );

	/* Resets the event manually. */
	void (*reset_event)(struct ThreadEvent* evt);

	/* Sets the event. */
	void (*set_event)(struct ThreadEvent* evt);

	/* Returns true if the event is set. */
	int (*is_event_set)(struct ThreadEvent* evt);

	/* Wait for the event to become set. */
	void (*wait_for_event)(struct ThreadEvent* evt);

	/* Wait for the event to become set with a maximum timeout specified in milliseconds. */
	int (*wait_for_event_timeout)(struct ThreadEvent* evt, unsigned timeout_ms);

	/* Creates a critical section for thread protection and locking. */
	struct ThreadCriticalSection* (*create_critical_section)(struct AllocatorObject *allocator);

	/* Destroys a critical section created by create_critical_section(). */
	void (*destroy_critical_section)(struct ThreadCriticalSection* cs,
		struct AllocatorObject *allocator);

	/* Enters the critical section. This will block if any other thread is already in the
	   critical section. */
	void (*enter_critical_section)(struct ThreadCriticalSection* cs);

	/* Leaves the critical section. */
	void (*leave_critical_section)(struct ThreadCriticalSection* cs);

	/* Tries to enter the critical section. This function won't block, instead it will return
	   false if another thread is already in the critical section, and true otherwise. */
	int (*try_to_enter_critical_section)(struct ThreadCriticalSection* cs);

	/* Returns the current assigned thread index. */
	unsigned (*worker_thread_index)();

	/* Assign to the current thread a worker thread index */
	void (*assign_worker_thread_index)();

	/* Reserved for expansion of the API. */
	void *reserved[30];
};

/* ----------------------------------------------------------------------
	TimerApi
---------------------------------------------------------------------- */

/*
	API for accessing the game timer.
*/
struct TimerApi
{
	/* Returns the number of ticks elapsed. The length of a tick is platform dependent, you need
	   to use ticks_to_seconds() to convert it to a real world number. */
	uint64_t (*ticks)();

	/* Converts ticks to seconds. */
	double (*ticks_to_seconds)(uint64_t ticks);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	StreamCaptureApi
---------------------------------------------------------------------- */

/* Describes a captured buffer. */
struct SC_Buffer {
	/* Frame number. */
	uint32_t frame;

	/* Format descriptor, use RenderBufferApi to interpret */
	uint32_t format;

	/* Surface dimension */
	uint32_t width;
	uint32_t height;

	/* Buffer data. */
	void *data;
};

/*
	Interface for capturing buffer data (render targets, etc) from the engine.
*/
struct StreamCaptureApi
{
	/* Enables stream capture of the named buffers. */
	void (*enable_capture)(void *window, uint32_t n_buffers, uint32_t *buffer_names);

	/* Disables stream capture for the named buffers. */
	void (*disable_capture)(void *window, uint32_t n_buffers, uint32_t *buffer_names);

	/* Extracts data from the named capture modifier into the output buffer. Returns true if
	   successful.

	   The captured data is allocated with the specified allocator. It is the responsibility of
	   the caller to deallocate the data pointer in the SC_Buffer. */
	uint8_t (*capture_buffer)(void *window, uint32_t name, struct AllocatorObject *allocator,
		struct SC_Buffer *output);

	/* Returns the name of a stream capture modifier */
	const char* (*capture_target_name)(CApiCaptureBufferPtr buffer);

	/* Returns an opaque pointer to a stream capture modifier */
	CApiCaptureBufferPtr (*capture_target)(unsigned index);

	/* Returns the length of currently available stream capture modifiers */
	unsigned (*num_available_capture_targets)();

	/* Returns the amount of used capture buffers to buffer capture data */
	unsigned (*num_used_buffers)();

	/* Reserved for expansion of the API. */
	void *reserved[31];
};

/* ----------------------------------------------------------------------
	FlowApi
---------------------------------------------------------------------- */

/* Opaque struct representing the context in which flow events are triggered. */
struct FlowTriggerContext;

/* Opaque struct representing a set of output events for a flow node. */
struct FlowOutputEvents;

/* Identifier for the special query event, which is sent to query nodes to get them to update
	their data. */
#define PLUGIN_QUERY_EVENT	0xffff

typedef uint32_t FlowNodeType;

/* Data for a flow trigger event. */
struct FlowData
{
	/* An integer identifying the type of the flow node. */
	FlowNodeType node_type;

	/* Identifier for the node. */
	unsigned short node;

	/* Index of the in event that was triggered on the flow node. */
	unsigned short event_index;

	/* Opaque struct that represents the out events of the flow node. Can be used to trigger out
	   events. */
	const struct FlowOutputEvents* out_events;
};

/* Maximum number of parameters to a flow node. */
#define PLUGIN_FLOW_NODES_MAX_PARAMS 63

/* Maximum length of flow string variables. */
#define PLUGIN_FLOW_STRING_VARIABLE_LENGTH 128

/* Represents the parameters of a flow node. */
struct FlowParameters {
	const void* parameters[PLUGIN_FLOW_NODES_MAX_PARAMS + 1];
};

struct FlowString
{
	unsigned int is_id64;	// Always set to zero
	char plain[PLUGIN_FLOW_STRING_VARIABLE_LENGTH];
};

struct FlowId
{
	unsigned int is_id64;	// May be 0 or 1 for input, always 1 for output
	unsigned int padding;
	uint64_t id;
};

/* Callback function for performing an action when a flow node is triggered. */
typedef void (*FlowFunction)(struct FlowTriggerContext* tc, const struct FlowData *fd, const struct FlowParameters *fp);

/* Callback function for setting variables on the flow node. */
typedef void (*SetVariableFunction)(struct FlowTriggerContext* tc, const struct FlowParameters *fp, unsigned key, void *data);

/* Callback function for triggering an out event. */
typedef void (*EventCallbackFunction)(struct FlowTriggerContext* tc, const struct FlowData *fd, const struct FlowParameters *fp);

/*
	Type            Input field (can be null)                 Output field (not null)
	"unit"          const CApiUnitRef*                        CApiUnitRef*
	"actor"         const CApiActor*                          CApiActor*
	"mover"         const CApiMover*                          CApiMover*
	"vector3"       const CApiVector3*                        CApiVector3*
	"float"         const float*                              float*
	"bool"          const unsigned*                           unsigned*
	"string"        const FlowString*                         FlowString*
	"id"            const FlowId*                             FlowId*
	"quaternion"    const CApiQuaternion*                     CApiQuaternion*
	"unsigned"      const unsigned*                           unsigned*
	"camera"        const CApiCamera*                         CApiCamera*
	"light"         const CApiLight*                          CApiLight*
	"mesh"          const CApiMesh*                           CApiMesh*
	"material"      const CApiMaterial*                       CApiMaterial*
	"resource"      const FlowString*
	"enum"          int
*/

/*
	Interface for implementing custom flow nodes.
*/
struct FlowNodesApi
{
	/* Registers a flow trigger function for a flow node with the specified name. */
	void (*setup_trigger_function)(unsigned name_id32, FlowFunction trigger_function);

	/* Registers an event callback for a flow node with the specified name. */
	void (*setup_event_callback)(unsigned name_id32, EventCallbackFunction event_callback_function);

	/* Registers a set_variable callback for a flow node with the specified name. */
	void (*setup_set_variable_callback)(unsigned name_id32, SetVariableFunction variable_callback_function);

	/* Unregisters the flow node with the specified name. */
	void (*unregister_flow_node)(unsigned name_id32);

	/* Used in the flow trigger implementation to trigger one of the flow node's out events. */
	void (*trigger_out_event)(struct FlowTriggerContext *tc, const struct FlowData* fd, int event_index);

	/* Used in the flow trigger implementation to trigger an external level event. */
	void (*trigger_external_level_event)(CApiLevel *level, unsigned id_string_32);

	/* Used in the flow trigger implementation to trigger an external unit event. */
	void (*trigger_external_unit_event)(CApiUnit *unit, unsigned id_string_32);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	CameraApi
---------------------------------------------------------------------- */

/* Camera mode. */
typedef enum
{
	C_MONO,
	C_STEREO
} C_Mode;

/* Camera projection. */
typedef enum
{
	C_ORTHOGRAPHIC,
	C_PERSPECTIVE
} C_ProjectionType;

/*
	Interface for manipulating cameras.
*/
struct CameraApi
{
	/* Returns the scene graph that owns the camera. */
	struct SceneGraph * (*scene_graph)(CApiCamera *camera);

	/* Returns the near range of the camera. */
	float (*near_range)(CApiCamera *camera);

	/* Sets the near range of the camera. */
	void (*set_near_range)(CApiCamera *, float near_range);

	/* Returns the far range of the camera. */
	float (*far_range)(CApiCamera *camera);

	/* Sets the far range of the camera. */
	void (*set_far_range)(CApiCamera *camera, float far_range);

	/* Returns the projection type of the camera. */
	uint8_t (*projection_type)(CApiCamera *camera);

	/* Sets the projection type of the camera. */
	void (*set_projection_type)(CApiCamera *camera, uint8_t projection_type);

	/* Returns the vertical FOV of the camera. */
	float (*vertical_fov)(CApiCamera *camera, unsigned i);

	/* Sets the vertical FOV of the camera. */
	void (*set_vertical_fov)(CApiCamera *camera, float fov, unsigned i);

	/* Sets the dimensions of the specified camera frustum. */
	void (*set_frustum)(CApiCamera *camera, float left, float right, float bottom, float top,
		unsigned i);
	void (*set_frustum_shear)(CApiCamera *camera, float shear_x, float shear_y, unsigned i);

	/* Sets the half angles of the specifies camera frustum. */
	void (*set_frustum_half_angles)(CApiCamera *camera, float left_tan, float right_tan,
		float bottom_tan, float top_tan, unsigned i);

	/* Returns the camera mode. */
	uint8_t (*mode)(CApiCamera *camera);

	/* Sets the camera mode. */
	void (*set_mode)(CApiCamera *camera, uint8_t mode);

	/* Sets the local position of the camera. */
	void (*set_local)(CApiCamera *camera, ConstMatrix4x4Ptr offset, unsigned i);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

/* ----------------------------------------------------------------------
	PhysicsRuntimeCookingApi
---------------------------------------------------------------------- */

/*
	API for doing runtime physics compilation of meshes into physics actors. Currently only supported on UWP.
*/

/* Description of the triangle mesh to cook */
typedef struct MeshDescription
{
	unsigned num_vertices;
	unsigned vertice_stride;
	void *vertices;
	unsigned num_triangles;
	unsigned triangle_stride;
	void *triangles;
} MeshDescription;

struct PhysicsRuntimeCookingApi
{
	/* Setup and initialize the physics cooking */
	void (*setup)();

	/* Shutdown the physics cooking */
	void (*shutdown)();

	/* Cooks a mesh and returns a pointer to the cooked mesh data allocated in the supplied allocator*/
	void *(*cook_mesh)(const MeshDescription *mesh_description, struct AllocatorObject *allocator);

	/* Creates a physics mesh from cooked data */
	void *(*create_physics_mesh)(const void *cooked_mesh);

	/* Releases physics mesh */
	void (*release_physics_mesh)(void *physics_mesh);

	/* Reserved for expansion of the API. */
	void *reserved[32];
};

#ifdef __cplusplus
}
#endif
