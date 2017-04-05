#pragma once

#include "assert.h"

namespace stingray_plugin_foundation {

// Convert integer to type.
template <int v>
struct Int2Type { enum {value=v}; };

// Determines if a class is allocator aware.
template <class T>
struct is_allocator_aware {

	template <typename C>
	static char test_fun(typename C::allocator_aware *);

	template <typename C>
	static int test_fun(...);

public:
	enum {
		value = (sizeof(test_fun<T>(0)) == sizeof(char))
	};
};

#define IS_ALLOCATOR_AWARE(T) is_allocator_aware<T>::value
#define IS_ALLOCATOR_AWARE_TYPE(T) Int2Type< IS_ALLOCATOR_AWARE(T) >

// Allocator aware constuction
template <class T> inline T &construct(void *p, Allocator &a, Int2Type<true>) {new (p) T(a); return *(T *)p;}

template <class T> inline T &construct(void *p, Allocator &a, Int2Type<false>) {new (p) T; return *(T *)p;}

template <class T> inline T &construct(void *p, Allocator &a) {return construct<T>(p, a, IS_ALLOCATOR_AWARE_TYPE(T)());}

// Helper for casts using a union. This circumvents the aliasing problem that occurs when
// trying to reinterpret a float as int and vice versa for example.
template<typename A, typename B>
A safe_reinterpret_cast(const B &b) {
	static_assert(sizeof(A) == sizeof(B), "Types must have same size to be cast");
	union U {
		A a;
		B b;
	} u;
	u.b = b;
	return u.a;
}

}

