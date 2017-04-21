#pragma once

#include "../engine_plugin_api/plugin_api.h"
#include "id_string.h"

namespace stingray_plugin_foundation {

	inline const char *get_c_string(const FlowString& flow_string)
	{
		XENSURE(flow_string.is_id64 == 0);
		return flow_string.plain;
	}

	inline void set_c_string(FlowString& flow_string, const char *string)
	{
		flow_string.is_id64 = 0;
		if (string == nullptr)
			flow_string.plain[0] = 0;
		strncpy(flow_string.plain, string, PLUGIN_FLOW_STRING_VARIABLE_LENGTH);
	}

	inline IdString64 get_id64(const FlowId* flow_id)
	{
		if (flow_id == nullptr)
			return IdString64();

		if (flow_id->is_id64 == 0)
			return IdString64(((const FlowString*)flow_id)->plain);

		return IdString64(flow_id->id);
	}

	inline const char *get_c_string(const FlowId* flow_id)
	{
		if (flow_id == nullptr)
			return nullptr;

		if (flow_id->is_id64 == 0)
			return ((const FlowString*)flow_id)->plain;

		return IdString64(flow_id->id).to_string();
	}

	inline void set_id64(FlowId& flow_id, IdString64 id)
	{
		flow_id.is_id64 = 1;
		flow_id.id = id.id();
	}


} // namespace stingray_plugin_foundation
