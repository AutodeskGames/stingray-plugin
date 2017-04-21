#pragma once

namespace stingray_plugin_foundation {

struct SceneFlags
{
	unsigned *_data;
	unsigned _allocated_flag_count;
	void *_allocator;

	// Sets the i'th flag
	inline void set(unsigned i) {
		i++;
#if defined(_DEBUG)
		XENSURE(i < _allocated_flag_count);
#endif
		_data[i/32] |= (1 << (i%32));
		set_any();
	}

	// Clears the i'th flag (does not update ANY flag).
	inline void clear(unsigned i) {
		i++;
#if defined(_DEBUG)
		XENSURE(i < _allocated_flag_count);
#endif
		_data[i/32] &= ~(1 << (i%32));
	}


protected:

	inline void set_any() {
#if defined(_DEBUG)
		XENSURE(_allocated_flag_count > 0);
#endif
		_data[0] |= 1;
	}
};

} // namespace stingray_plugin_foundation
