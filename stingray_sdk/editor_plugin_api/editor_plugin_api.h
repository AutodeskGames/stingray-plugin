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

/* Primitive config value types */
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

	union {
		void* _allocator;
		void* _object;
		void* _array;
		void* _data;
	};
};
typedef struct ConfigValueStruct* ConfigValue;
typedef const ConfigValue ConstConfigValue;
typedef ConfigValueStruct* ConfigValueArgs;
typedef ConfigValue* ConfigValueResult;

struct ConfigHandleObject;
typedef ConfigHandleObject* ConfigHandle;

/* Callback used to deallocate a config value user handle */
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
	/* Create a new config value. It's type will be defined when you assign a value */
	ConfigValue (*make)(EditorAllocator allocator);

	/* Releases the memory used by the config value. */
	void (*free)(ConfigValue value);

	/* Creates a config value that is null. */
	ConfigValue(*nil)();

	/* Returns the type of a config value, see CD_TYPE_* */
	int (*type)(ConfigValue value);

	/* Returns the boolean value of the config value. */
	int (*to_bool)(ConfigValue value);

	/* Returns the numerical value of the config value. */
	double (*to_number)(ConfigValue value);

	/* Returns the string value of the config value. */
	const char *(*to_string)(ConfigValue value);

	/* Returns the user handle of the config value. */
	ConfigHandle (*to_handle)(ConfigValue value);

	/* Returns the deallocator of the user handle config value. */
	cd_handle_dealloc (*to_handle_deallocator)(ConfigValue value);

	/* Defines the config value as a boolean value. */
	void(*set_bool)(ConfigValue value, int b);

	/* Defines the config value as a numerical value. */
	void(*set_number)(ConfigValue value, double n);

	/* Defines the config value as a string value. */
	void(*set_string)(ConfigValue value, const char *s);

	/* Defines the config value as a user handle. */
	void(*set_handle)(ConfigValue value, ConfigHandle handle, cd_handle_dealloc deallocator);

	/* Defines the config value as an array. */
	ConfigValueArgs(*set_array)(ConfigValue value, int size);

	/* Defines the config value as an object. */
	void(*set_object)(ConfigValue value);

	/* Returns the number of element of the config value. */
	int (*array_size)(ConfigValue arr);

	/* Returns an element config value of a config value array. */
	ConfigValue (*array_item)(ConfigValue arr, int i);

	/* Adds an elements to a config value array. */
	ConfigValue (*push)(ConfigValue array, ConfigValue item);

	/* Returns the number of properties of a config value object. */
	int (*object_size)(ConfigValue object);

	/* Returns the property name of an object field. */
	const char *(*object_key)(ConfigValue object, int i);

	/* Returns the property value of an object field. */
	ConfigValue(*object_value)(ConfigValue object, int i);

	/* Returns the property value of an object field by matching its property
	 * key if it exists. */
	ConfigValue(*object_lookup)(ConfigValue object, const char *key);

	/* Adds a null property. */
	ConfigValue(*add_nil)(ConfigValue object, const char *key);

	/* Adds a boolean property. */
	ConfigValue(*add_bool)(ConfigValue object, const char *key, int b);

	/* Adds a numerical property. */
	ConfigValue(*add_number)(ConfigValue object, const char *key, double n);

	/* Adds a string property. */
	ConfigValue(*add_string)(ConfigValue object, const char *key, const char* s);

	/* Adds an object property. */
	ConfigValue(*add_object)(ConfigValue object, const char *key, ConfigValue o);

	/* Adds an array property. */
	ConfigValue(*add_array)(ConfigValue object, const char *key, ConfigValue a);

	/* Alias to object_lookup, to find a property by name. */
	ConfigValue(*get)(ConfigValue object, const char *key);

	/* Sets the config value of a property by name. */
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
