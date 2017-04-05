#pragma once

#include "../c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct TagComponentCApi
{
	// Fills the specified buffer with up to (buffer_size) number of entities that has the tag.
	// Returns the total number of entities the tag has.
	unsigned (*get_entities)(TagComponentPtr comp, unsigned tag_id32, EntityRef *buffer, unsigned buffer_size);

	void (*add_tag)(TagComponentPtr comp, EntityRef e_ref, unsigned tag_id32);
	void (*remove_tag)(TagComponentPtr comp, EntityRef e_ref, unsigned tag_id32);
	int (*has_tag)(TagComponentPtr comp, EntityRef e_ref, unsigned tag_id32);
};

#ifdef __cplusplus
}
#endif
