
#include <editor_plugin_api/editor_plugin_api.h>

namespace PLUGIN_NAMESPACE {

ConfigDataApi* config_data_api = nullptr;
EditorLoggingApi* logging_api = nullptr;
EditorEvalApi* eval_api = nullptr;
EditorAllocatorApi* allocator_api = nullptr;
EditorAllocator plugin_allocator = nullptr;

/**
 * Return plugin extension name.
 */
const char* get_name() { return "Editor Plugin Extension"; }

/**
 * Return plugin version.
 */
const char* get_version() { return "1.0.0"; }

/**
 * Log received arguments arguments and return a copy of the first one.
 */
ConfigValue test_log_arguments(ConfigValueArgs args, int num)
{
	if (num < 1)
		return nullptr;

	// Log all string arguments to the editor console.
	for (auto i = 0; i < num; ++i) {
		auto argument = &args[i];
		if (config_data_api->type(argument) == CD_TYPE_STRING)
			logging_api->info(config_data_api->to_string(argument));
	}

	// Evaluate some JavaScript from the editor extension.
	eval_api->eval("console.warn(`The answer to life the universe and everything equals ${21 + 21}`);", nullptr, nullptr);

	// Clone first argument and return it.
	auto first_arg = &args[0];
	auto copy_cv = config_data_api->make(nullptr);
	auto type = config_data_api->type(first_arg);
	switch (type) {
		case CD_TYPE_NULL: return config_data_api->nil();
		case CD_TYPE_FALSE: config_data_api->set_bool(copy_cv, false); break;
		case CD_TYPE_TRUE: config_data_api->set_bool(copy_cv, true); break;
		case CD_TYPE_NUMBER: config_data_api->set_number(copy_cv, config_data_api->to_number(first_arg)); break;
		case CD_TYPE_STRING: config_data_api->set_string(copy_cv, config_data_api->to_string(first_arg)); break;
		case CD_TYPE_ARRAY:
		{
			auto length = config_data_api->array_size(first_arg);
			for (auto i = 0; i < length; ++i) {
				auto origin_item = config_data_api->array_item(first_arg, i);
				config_data_api->push(copy_cv, origin_item);
			}
			break;
		}
		case CD_TYPE_OBJECT:
		{
			auto size = config_data_api->object_size(first_arg);
			config_data_api->set_object(copy_cv);
			for (auto i = 0; i < size; ++i) {
				auto object_item_key = config_data_api->object_key(first_arg, i);
				auto object_item_value = config_data_api->object_value(first_arg, i);
				config_data_api->set(copy_cv, object_item_key, object_item_value);
			}
			break;
		}
		default: break;
	}

	return copy_cv;
}

/*
 * Create a new config value using a custom allocator.
 */
ConfigValue test_custom_allocator(ConfigValueArgs args, int num)
{
	auto cvca = config_data_api->make(plugin_allocator);
	config_data_api->set_string(cvca, "This was allocator with a custom plugin allocator.");
	return cvca;
}

/*
 * Allocator function used by our test plugin custom allocator.
 * We use as an example a static buffer to write up to 1024 bytes of data.
 */
void* test_custom_allocate(size_t size, size_t align, void *param)
{
	static unsigned char small_buffer[1024] = { 0 };
	static size_t small_buffer_cursor = 0;

	if (small_buffer_cursor+size > sizeof small_buffer) {
		logging_api->error("We do not have enough space!");
		return nullptr;
	}
	
	logging_api->info("We have enough space!");
	auto pi = small_buffer_cursor;
	small_buffer_cursor += size;
	return small_buffer + pi;
}

/*
 * Deallocation function used by our test plugin allocator.
 * We do not release any memory since the allocator writes to a static buffer.
 */
size_t test_custom_deallocate(void* ptr, void *param)
{
	logging_api->debug("We do not deallocate in the fixed small_buffer.");
	return 0;
}

/**
 * Setup plugin resources and define client JavaScript APIs.
 */
void plugin_loaded(GetEditorApiFunction get_editor_api)
{
	auto api = static_cast<EditorApi*>(get_editor_api(EDITOR_API_ID));
	config_data_api = static_cast<ConfigDataApi*>(get_editor_api(CONFIGDATA_API_ID));
	logging_api = static_cast<EditorLoggingApi*>(get_editor_api(EDITOR_LOGGING_API_ID));
	eval_api = static_cast<EditorEvalApi*>(get_editor_api(EDITOR_EVAL_API_ID));
	allocator_api = static_cast<EditorAllocatorApi*>(get_editor_api(EDITOR_ALLOCATOR_ID));

	plugin_allocator = allocator_api->create("example_allocator", test_custom_allocate, test_custom_deallocate, nullptr);

	api->register_native_function("example", "test_log_arguments", &test_log_arguments);
	api->register_native_function("example", "test_custom_allocator", &test_custom_allocator);
}

/**
 * Release plugin resources and exposed APIs.
 */
void plugin_unloaded(GetEditorApiFunction get_editor_api)
{
	auto api = static_cast<EditorApi*>(get_editor_api(EDITOR_API_ID));
	api->unregister_native_function("example", "test_log_arguments");
	api->unregister_native_function("example", "test_custom_allocator");

	allocator_api->destroy(plugin_allocator);
}

} // end namespace

/**
 * Setup plugin APIs.
 */
extern "C" __declspec(dllexport) void *get_editor_plugin_api(unsigned api)
{
	if (api == EDITOR_PLUGIN_SYNC_API_ID) {
		static struct EditorPluginSyncApi editor_api = {nullptr};
		editor_api.get_name = &PLUGIN_NAMESPACE::get_name;
		editor_api.get_version = &PLUGIN_NAMESPACE::get_version;
		editor_api.plugin_loaded = &PLUGIN_NAMESPACE::plugin_loaded;
		editor_api.shutdown = &PLUGIN_NAMESPACE::plugin_unloaded;
		return &editor_api;
	}

	return nullptr;
}
