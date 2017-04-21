#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
	This file defines the Plugin API for the editor.

	The plugin interface is based around a single function:

		__declspec(dllexport) void *get_editor_plugin_api(unsigned plugin_api_id);

	The API ID is an integer that uniquely identify a specific version of a particular service.
	If the plugin can provide the service it returns a pointer to an API struct that contains
	function pointers for using the service.

	For ABI compatibility and simplicity, only C code is used in the interfaces.

	This method is used both by the plugins to provide services to the editor and by the editor
	to provide services to the plugins. For the second case, the editor sends a function:

		void *get_editor_api(unsigned api_id);

	To the plugins when they are initialized. The plugins can use this function to query for
	editor interfaces.

	If you need to make big changes to an API, so that it is no longer backwards compatible
	with the old API, you should create a new API_ID identifier and make sure that the old
	API_ID identifier still returns the old API. That way, the code will continue to work
	with older plugins that use the old API, while still providing new functionality in the
	new API.

	Note that during development, the APIs may change frequently. It is only when we lock an
	API down for public release that we need to be careful about version management and
	backwards compatibility.

	Note that all the functions in the APIs are not described in this header file, because in
	many cases they are just thin wrappers around existing editor systems.
*/

/* Plugin API_IDs for the different services that a plugin can implement. */
enum EditorPluginApiID
{
	EDITOR_PLUGIN_SYNC_API_ID = 0,
	EDITOR_PLUGIN_ASYNC_API_ID
};

/* Editor API_IDs for the different services the editor offers. */
enum EditorApiID {
	EDITOR_API_ID = 0,
	EDITOR_API_V2_ID = 1,
	CONFIGDATA_API_ID = 2,
	EDITOR_LOGGING_API_ID = 3,
	EDITOR_EVAL_API_ID = 4,
	EDITOR_ASYNC_API_ID = 5
#if defined(_FUNCTIONAL_)
	, EDITOR_API_V3_ID = 6
#endif
	, EDITOR_ALLOCATOR_ID = 7
};

enum ProcessId
{
	BROWSER = 0,
	RENDERER
};

#define CONFIG_DATA_VALUE_TYPE_BITS 3
#define CONFIG_DATA_VALUE_TAG_BITS 29

enum {
	CD_TYPE_NULL = 0,
	CD_TYPE_BOOL = 1,
	CD_TYPE_NUMBER = 2,
	CD_TYPE_STRING = 3,
	CD_TYPE_HANDLE = 4,
	CD_TYPE_ARRAY = 5,
	CD_TYPE_OBJECT = 6,
	CD_TYPE_TRUE, CD_TYPE_FALSE,
	CD_TYPE_UNDEFINED = CD_TYPE_NULL
};

struct ConfigValueStruct {
	struct {
		unsigned type : CONFIG_DATA_VALUE_TYPE_BITS;
		unsigned tag : CONFIG_DATA_VALUE_TAG_BITS;
	};

	union {
		double _number;
		bool _bool;
	};

	void* reserved;
};
typedef struct ConfigValueStruct* ConfigValue;
typedef const ConfigValue ConstConfigValue;
typedef ConfigValueStruct* ConfigValueArgs;
typedef ConfigValue* ConfigValueResult;

struct ConfigHandleObject;
typedef ConfigHandleObject* ConfigHandle;

typedef union
{
	int boolean;
	int int32;
	double number;
	const char* str;
	ConfigHandle handle;
	ConfigValue obj;
	ConfigValue arr;
} ConfigPrimitiveValue;

typedef void(*cd_handle_dealloc)(ConfigHandle handle);


/* This function can be used by the plugin to query for editor API. */
typedef void *(*GetEditorApiFunction)(unsigned api);

/*
	This is the main interface provided by the plugins. The functions in this interface will
	be called at various points during the editor's setup and shutdown sequence.

	The plugin is not obligated to implement all these functions. You can return NULL for the
	functions that you do not support.
*/
struct EditorPluginSyncApi
{
	/* Called once the plugin has been loaded. */
	void (*plugin_loaded)(GetEditorApiFunction get_editor_api);

	/* Returns the name of the plugin. */
	const char *(*get_name)();

	/* Returns the version of the plugin. A version is a string of format 1.0.0.0 */
	const char *(*get_version)();

	/* Called when the plugins needs to be shutdown */
	void (*shutdown)(GetEditorApiFunction get_editor_api);
};

struct EditorPluginAsyncApi
{
	/* Called once the plugin has been loaded. */
	void (*plugin_loaded)(GetEditorApiFunction get_editor_api);

	/* Returns the name of the plugin. */
	const char *(*get_name)();

	/* Returns the version of the plugin. A version is a string of format 1.0.0.0 */
	const char *(*get_version)();

	/* Called when the plugins needs to be shutdown */
	void (*shutdown)(GetEditorApiFunction get_editor_api);
};

struct EditorApi
{
	typedef ConfigValue (*NativeFunctionHandler)(ConfigValueArgs args, int num);

	/* Used to register a synchronous function that is executed on the render thread. Can be called using namespace.YOURFUNCTIONNAME(); */
	bool (*register_native_function)(const char *ns, const char *name, NativeFunctionHandler handler);

	/* Used to unregister a previously registered native function. */
	bool (*unregister_native_function)(const char *ns, const char *name);
};

struct EditorApi_V2
{
	typedef ConfigValue (*NativeFunctionHandler)(ConfigValueArgs args, int num, GetEditorApiFunction get_editor_api);

	/* Used to register a synchronous function that is executed on the render thread. Can be called using namespace.YOURFUNCTIONNAME(); */
	bool (*register_native_function)(const char *ns, const char *name, NativeFunctionHandler handler);

	/* Used to unregister a previously registered native function. */
	bool (*unregister_native_function)(const char *ns, const char *name);
};

struct EditorAsyncApi
{
	typedef ConfigValue (*AsyncFunctionHandler)(ConfigValueArgs args, int num, GetEditorApiFunction get_editor_api);

	/* Used to register an asynchronous function that is executed on the browser thread. Can be called using stingray.hostExecute('your-function-name', ...); */
	bool (*register_async_function)(const char *name, AsyncFunctionHandler handler);

	/* Used to unregister a previously registered async function. */
	bool (*unregister_async_function)(const char *name);

	/* Used to register an asynchronous function that is executed on the gui thread. Can be called using stingray.hostExecute('your-function-name', ...); */
	bool (*register_async_gui_function)(const char *name, AsyncFunctionHandler handler);

	/* Used to unregister a previously registered async gui function. */
	bool (*unregister_async_gui_function)(const char *name);
};

struct EditorAllocatorObject;
typedef EditorAllocatorObject* EditorAllocator;
typedef void * (*EditorAllocateHandler) (size_t size, size_t align, void *param);
typedef size_t (*EditorDeallocateHandler) (void* ptr, void *param);

struct EditorAllocatorApi
{
	EditorAllocator (*system_default)();
	EditorAllocator (*create)(const char* name, EditorAllocateHandler alloc_handler, EditorDeallocateHandler dealloc_handler, void* user_data);
	void (*destroy)(EditorAllocator);
};

struct ConfigDataApi
{
	ConfigValue (*make)(EditorAllocator allocator);
	ConfigValue(*from_type)(int type, ConfigPrimitiveValue data, EditorAllocator allocator);
	void (*free)(ConfigValue value);
	ConfigValue(*nil)();

	int (*type)(ConfigValue value);
	int (*to_bool)(ConfigValue value);
	double (*to_number)(ConfigValue value);
	const char *(*to_string)(ConfigValue value);
	ConfigHandle (*to_handle)(ConfigValue value);
	cd_handle_dealloc (*to_handle_deallocator)(ConfigValue value);

	void(*set_bool)(ConfigValue value, int b);
	void(*set_number)(ConfigValue value, double n);
	void(*set_string)(ConfigValue value, const char *s);
	void(*set_handle)(ConfigValue value, ConfigHandle handle, cd_handle_dealloc deallocator);
	ConfigValueArgs(*set_array)(ConfigValue value, int size);
	void(*set_object)(ConfigValue value);

	int (*array_size)(ConfigValue arr);
	ConfigValue (*array_item)(ConfigValue arr, int i);
	ConfigValue (*push)(ConfigValue array, ConfigValue item);

	int (*object_size)(ConfigValue object);
	const char *(*object_key)(ConfigValue object, int i);
	ConfigValue(*object_value)(ConfigValue object, int i);
	ConfigValue(*object_lookup)(ConfigValue object, const char *key);
	ConfigValue(*add_nil)(ConfigValue object, const char *key);
	ConfigValue(*add_bool)(ConfigValue object, const char *key, int b);
	ConfigValue(*add_number)(ConfigValue object, const char *key, double n);
	ConfigValue(*add_string)(ConfigValue object, const char *key, const char* s);
	ConfigValue(*add_object)(ConfigValue object, const char *key, ConfigValue o);
	ConfigValue(*add_array)(ConfigValue object, const char *key, ConfigValue a);
	ConfigValue(*get)(ConfigValue object, const char *key);
	ConfigValue(*set)(ConfigValue object, const char *key, ConfigValue value);
};

struct EditorLoggingApi
{
	/* Used to print only in the dev tools console. */
	void (*debug)(const char *message);

	/* Used to print an information in the stingray console. */
	void (*info)(const char *message);

	/* Used to print a warning in the stingray console. */
	void (*warning)(const char *message);

	/* Used to print an error in the stingray console. */
	void (*error)(const char *message);
};

struct EditorEvalApi
{
	/* Used to evaluate a javascript code in the global context. `return_value` and `exception` are optional.
	 * If an exception is thrown and `exception` is not null, it will be populated with an object
	 * {'message': exception_message}.
	 */
	bool (*eval)(const char *js_code, ConfigValue return_value, ConfigValue exception);
};

#ifdef __cplusplus
}
#endif


#if defined(__cplusplus) && defined(_FUNCTIONAL_)
struct EditorApi_V3
{
	typedef std::function<ConfigValue(ConfigValueArgs, int)> NativeFunctionHandler;

	/* Used to register a synchronous function that is executed on the render thread. Can be called using namespace.YOURFUNCTIONNAME(); */
	bool (*register_native_function)(const char *ns, const char *name, NativeFunctionHandler handler);

	/* Used to unregister a previously registered native function. */
	bool (*unregister_native_function)(const char *ns, const char *name);
};
#endif
