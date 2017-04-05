#pragma once

#include "../engine_plugin_api/plugin_api.h"

#define _XKEYCHECK_H
#define alignof(x)	__alignof(x)

namespace stingray_plugin_foundation {

// Abstract base class for allocators.
//
// Allocators can be thread-safe or not, see the separate documentation for each
// alloactor.
class Allocator
{
	Allocator(const Allocator &);
	Allocator & operator=(const Allocator &);

public:
	static const int DEFAULT_ALIGN = 4;

	Allocator() {}
	virtual ~Allocator() {}

	// Convenience method for allocating when you don't care about allocated size.
	virtual void *allocate(size_t size, unsigned align = DEFAULT_ALIGN) = 0;

	// Frees the memory pointed to by p, the memory must have been allocated by the allocate()
	// function. Returns the size of the allocated memomry.
	virtual size_t deallocate(void *p) = 0;
};

// Allocator class that wraps the AllocatorApi exposed by the engine's plugin interface.
class ApiAllocator : public Allocator
{
	AllocatorObject *_object;
	AllocatorApi *_api;

public:
	ApiAllocator(AllocatorApi *api, AllocatorObject *object) : _object(object), _api(api) {}
	ApiAllocator(const ApiAllocator &a) : _object(a._object), _api(a._api) {}
	ApiAllocator & operator=(const ApiAllocator &a) { _object = a._object; _api = a._api; return *this; }

	virtual void *allocate(size_t size, unsigned align = DEFAULT_ALIGN) override {return _api->allocate(_object, size, align);}
	virtual size_t deallocate(void *p) override {return _api->deallocate(_object, p);}

	AllocatorObject *object() { return _object; }
	AllocatorApi *api() { return _api; }
};

template <class T> void make_delete(Allocator &a, T *p) {
	if (p) {
		p->~T();
		a.deallocate(p);
	}
}

// Allocator that allocates from a static buffer.
class StaticAllocator : public Allocator
{
	char *_start;
	char *_p;
	char *_end;

public:
	StaticAllocator(char *p, char *end) : _start(p), _p(p), _end(end) {}

	virtual void *allocate(size_t size, unsigned align = DEFAULT_ALIGN) override
	{
		if (size == 0)
			return nullptr;

		unsigned rem = (_p - (const char *)0) % align;
		if (rem)
			_p += (align - rem);
		char *ret = _p + size > _end ? nullptr : _p;
		_p += size;
		return ret;
	}

	size_t deallocate(void *p) override { return 0; }

	char *start() {return _start;}
	bool out_of_memory() {return _p > _end;}
	size_t wanted_memory() {return (size_t)(_p - _start);}
};

// Allocations released only by destructor
class TempAllocator : public ApiAllocator
{
public:
	TempAllocator(AllocatorApi *api) : ApiAllocator(api, api->make_temp_allocator()) {}
	virtual ~TempAllocator() { api()->destroy_temp_allocator(object()); }
};

// Add this in the public section of classes to specify that they want to be initialized with an
// allocator.
#define ALLOCATOR_AWARE typedef int allocator_aware

// Macro versions of make_new and make_delete to avoid template combinatorial explosion and
// make sure errors are reported in the file where the macro is called.
#define MAKE_NEW(a, T, ...)			(new ((a).allocate(sizeof(T), alignof(T))) T(__VA_ARGS__))
#define MAKE_DELETE(a, p)			(make_delete(a,p))
#define MAKE_DELETE_TYPE(a, T, p)	do {if (p) {(p)->~T(); (a).deallocate(p);}} while (0)

} // namespace stingray_plugin_foundation
