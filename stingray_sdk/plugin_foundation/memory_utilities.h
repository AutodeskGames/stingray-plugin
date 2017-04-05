#pragma once

namespace stingray_plugin_foundation {

namespace memory_utilities {

// Rounds size up to the specified alignment
template <class T>
inline T round_up_to(T size, unsigned align)
{
	return ((size + align - 1) / align) * align;
}

// Returns true if p is aligned to the specified alignment
inline bool is_aligned(const void *p, unsigned align)
{
	uintptr_t pi = (uintptr_t)p;
	return pi % align == 0;
}

// Returns the result of advancing p by the specified number of bytes
inline void *pointer_add(void *p, size_t bytes)
{
	return (void*)((char *)p + bytes);
}
inline const void *pointer_add(const void *p, size_t bytes)
{
	return (const void*)((const char *)p + bytes);
}


// Returns the result of moving p back by the specified number of bytes
inline void *pointer_sub(void *p, size_t bytes)
{
	return (void*)((char *)p - bytes);
}
inline const void *pointer_sub(const void *p, size_t bytes)
{
	return (const void*)((const char *)p - bytes);
}
inline size_t pointer_sub(const void *p1, const void *p2)
{
	return (const char *)p1 - (const char *)p2;
}

// The number of bytes p must be moved forward to align
inline unsigned bytes_to_aligned_address(const void *p, unsigned align)
{
	uintptr_t pi = (uintptr_t)p;
	return (unsigned)(((pi + align - 1)/align)*align - pi);
}

// The number of bytes p must be moved backward to align
inline unsigned bytes_from_aligned_address(const void *p, unsigned align)
{
	uintptr_t pi = (uintptr_t)p;
	return pi % align;
}

// Moves p forward to align
inline void *round_up_to_aligned_address(void *p, unsigned align)
{
	return pointer_add(p, bytes_to_aligned_address(p, align));
}
inline const void *round_up_to_aligned_address(const void *p, unsigned align)
{
	return pointer_add(p, bytes_to_aligned_address(p, align));
}

// Moves p backward to align
inline void *round_down_to_aligned_address(void *p, unsigned align)
{
	return pointer_sub(p, bytes_from_aligned_address(p, align));
}
inline const void *round_down_to_aligned_address(const void *p, unsigned align)
{
	return pointer_sub(p, bytes_from_aligned_address(p, align));
}

// Interprets data at address p as an object of type T.
template<class T>
inline T& object_at_address(void *p)
{
	return *(T *)p;
}
template<class T>
inline const T& object_at_address(const void *p)
{
	return *(T *)p;
}

}

}
