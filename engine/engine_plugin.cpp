#include <engine_plugin_api/plugin_api.h>
#include <plugin_foundation/platform.h>
#include <plugin_foundation/id_string.h>
#include <plugin_foundation/string.h>
#include <plugin_foundation/allocator.h>

#if _DEBUG
	#include <stdlib.h>
	#include <time.h>
#endif

namespace PLUGIN_NAMESPACE {

using namespace stingray_plugin_foundation;

// Common constants
unsigned int INVALID_HANDLE = UINT32_MAX;

// Engine APIs
DataCompilerApi *data_compiler = nullptr;
DataCompileParametersApi * data_compile_params = nullptr;
AllocatorApi *allocator_api = nullptr;
AllocatorObject *allocator_object = nullptr;
ApiAllocator _allocator(nullptr, nullptr);
LoggingApi *log = nullptr;
ErrorApi *error = nullptr;
UnitApi* unit = nullptr;
ResourceManagerApi* resource_manager = nullptr;
RenderBufferApi* render_buffer = nullptr;

// C Scripting API
namespace stingray {
	struct UnitCApi* Unit = nullptr;
	struct MeshCApi* Mesh = nullptr;
	struct MaterialCApi* Material = nullptr;
	struct DynamicScriptDataCApi* Data = nullptr;
}

// Data compiler resource properties
int RESOURCE_VERSION = 1;
const char *RESOURCE_EXTENSION = "my_file_extension";
const IdString64 RESOURCE_ID = IdString64(RESOURCE_EXTENSION);

/**
 * Returns the plugin name.
 */
const char* get_name() { return "engine_plugin"; }

/**
 * Clone the source resource data and append it's buffer size in front of the 
 * data result buffer.
 */
DataCompileResult pack_source_data_with_size(DataCompileParameters *input, const DataCompileResult& result_data)
{
	DataCompileResult result = { nullptr };
	unsigned length_with_data_size = result_data.data.len + sizeof(unsigned);
	result.data.p = (char*)allocator_api->allocate(data_compile_params->allocator(input), length_with_data_size, 4);
	result.data.len = length_with_data_size;
	memcpy(result.data.p, &result_data.data.len, sizeof(unsigned));
	memcpy(result.data.p + sizeof(unsigned), result_data.data.p, result_data.data.len);
	return result;
}

/**
 * Define plugin resource compiler.
 */
DataCompileResult my_resource_compiler(DataCompileParameters *input)
{
	auto source_data = data_compile_params->read(input);
	if (source_data.error)
		return source_data;
	return pack_source_data_with_size(input, source_data);
}

/**
 * Setup runtime and compiler common resources, such as allocators.
 */
void setup_common_api(GetApiFunction get_engine_api)
{
	allocator_api = (AllocatorApi*)get_engine_api(ALLOCATOR_API_ID);
	if (allocator_object == nullptr) {
		allocator_object = allocator_api->make_plugin_allocator(get_name());
		_allocator = ApiAllocator(allocator_api, allocator_object);
	}

	log = (LoggingApi*)get_engine_api(LOGGING_API_ID);
	error = (ErrorApi*)get_engine_api(ERROR_API_ID);
	resource_manager = (ResourceManagerApi*)get_engine_api(RESOURCE_MANAGER_API_ID);
}

/**
 * Setup plugin runtime resources.
 */
void setup_plugin(GetApiFunction get_engine_api)
{
	setup_common_api(get_engine_api);

	unit = (UnitApi*)get_engine_api(UNIT_API_ID);
	render_buffer = (RenderBufferApi*)get_engine_api(RENDER_BUFFER_API_ID);
	auto c_api = (ScriptApi*)get_engine_api(C_API_ID);
	stingray::Unit = c_api->Unit;
	stingray::Mesh = c_api->Mesh;
	stingray::Material = c_api->Material;
	stingray::Data = c_api->DynamicScriptData;
}

/**
 * Setup plugin compiler resources.
 */
void setup_data_compiler(GetApiFunction get_engine_api)
{
	setup_common_api(get_engine_api);

	#if _DEBUG
		// Always trigger the resource compiler in debug mode.
		srand(time(nullptr));
		RESOURCE_VERSION = rand();
	#endif

	data_compiler = (DataCompilerApi*)get_engine_api(DATA_COMPILER_API_ID);
	data_compile_params = (DataCompileParametersApi*)get_engine_api(DATA_COMPILE_PARAMETERS_API_ID);
	data_compiler->add_compiler(RESOURCE_EXTENSION, RESOURCE_VERSION, my_resource_compiler);
}

/**
 * Indicate to the resource manager that we'll be using our plugin resource type.
 */
void setup_resources(GetApiFunction get_engine_api)
{
	setup_common_api(get_engine_api);
	resource_manager->register_type(RESOURCE_EXTENSION);
}

/**
 * Called per game frame.
 */
void update_plugin(float dt)
{
	//log->info(get_name(), error->eprintf("Updating %f", dt));
}

/**
 * Release plugin resources.
 */
void shutdown_plugin()
{
	if (allocator_object != nullptr) {
		XENSURE(_allocator.api());
		_allocator = ApiAllocator(nullptr, nullptr);
		allocator_api->destroy_plugin_allocator(allocator_object);
		allocator_object = nullptr;
	}
}

}

extern "C" {

	/**
	 * Load and define plugin APIs.
	 */
	PLUGIN_DLLEXPORT void *get_plugin_api(unsigned api)
	{
		using namespace PLUGIN_NAMESPACE;

		if (api == PLUGIN_API_ID) {
			static PluginApi plugin_api = { nullptr };
			plugin_api.get_name = get_name;
			plugin_api.setup_game = setup_plugin;
			plugin_api.update_game = update_plugin;
			plugin_api.setup_resources = setup_resources;
			plugin_api.shutdown_game = shutdown_plugin;
			plugin_api.setup_data_compiler = setup_data_compiler;
			plugin_api.shutdown_data_compiler = shutdown_plugin;
			return &plugin_api;
		}
		return nullptr;
	}

}
