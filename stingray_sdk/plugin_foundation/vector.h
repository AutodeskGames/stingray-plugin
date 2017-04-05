#pragma once

#include "allocator.h"
#include "template_tools.h"
#include "assert.h"
#include "math.h"
#include <string.h> // memmove
#include <algorithm>

#if !defined(PS4)
	#pragma warning(disable:4345)
#endif

namespace stingray_plugin_foundation {

struct NoAllocator {};

// A replacement for the std::vector class.
//
// The main difference between an std::vector and this vector class, is that this vector
// uses a specific allocator (a pointer to the allocator is stored) and allocates all its
// memory through that allocator. This makes it easy to support various types of memory
// allocation strategies.
//
// This vector implementation assumes that the types are "raw-movable"... i.e. that they
// can be bit-wise copied from one memory location to another without invoking a copy-
// constructor and a destructor.
//
// Unimplemented functions from standard stl (add if needed):
//		- vector(unsigned n, const T& t)
//		- vector(InputIterator, InputIterator),
//		- rbegin()
//		- rend()
//		- max_size(),
//		- void insert(iterator pos, InputIterator f, InputIterator l)
//		- void insert(iterator pos, unsigned n, const T& x)
//		- void resize(n, t = T())
//		- bool operator==(const vector&, const vector&)
//		- bool operator<(const vector&, const vector&)
template <class T>
class Vector
{
public:
	ALLOCATOR_AWARE;

	// Type definitions

	typedef Vector<T>		this_type;
	typedef T               value_type;
	typedef T*              pointer;
	typedef const T*        const_pointer;
	typedef T&              reference;
	typedef const T&        const_reference;
	typedef	pointer			iterator;
	typedef const_pointer   const_iterator;

	// Constructors

	// Creates a vector that uses the specified allocator to allocate  memory.
	Vector(Allocator &allocator);

	// Creates a vector and presizes it to the specified size.
	Vector(unsigned size, Allocator &allocator);

	// Creates a vector without an allocator, one must be provided later with
	// set_allocator() before the vector is resized.
	Vector(const NoAllocator &);

	// Sets the allocator of the vector. You can only call this before any
	// allocations have been made by the vector.
	void set_allocator(Allocator &allocator);

	Vector( const Vector<T> &o );
	~Vector() {reset();}

	// Asignment operator -- note that we do not support chained assignments.
	void operator=(const Vector<T> &o);

	// Serializes the vector to the stream.
	template <class STREAM>	void serialize(STREAM &stream);

	// std::vector interface

	iterator begin() {return _data;}
	const_iterator begin() const {return _data;}
	iterator end() {return _data + _size;}
	const_iterator end() const {return _data + _size;}

	unsigned size() const {return _size;}
	unsigned capacity() const {return _capacity;}
	bool any() const {return _size != 0;}
	bool empty() const {return _size == 0;}

	reference operator[](unsigned i);
	const_reference operator[](unsigned i) const;

	void reserve(unsigned capacity);

	reference front() {XENSURE(_size > 0); return _data[0];}
	const_reference front() const {XENSURE(_size > 0); return _data[0];}
	reference back() {XENSURE(_size > 0); return _data[_size-1];}
	const_reference back() const {XENSURE(_size > 0); return _data[_size-1];}

	template <class ASSIGNABLE> void push_back(const ASSIGNABLE &item);
	void pop_back();

	void swap(Vector<T> &o);

	template <class ASSIGNABLE> iterator insert(iterator pos, const ASSIGNABLE & x);
	iterator insert(iterator pos);
	void insert(iterator pos, const_iterator from, const_iterator to);
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);

	void clear() {resize(0);}
	void resize(unsigned size);

	bool operator==(const Vector<T> &o) const;
	bool operator<(const Vector<T> &o) const;

	// Vector extensions

	// Resets the vector to initial state (no memory allocated).
	void reset() {set_capacity(0);}

	// Extends the vector with the specified number of elements.
	void extend(unsigned elements) { resize(size() + elements); }

	// Extends the vector with one elements and returns a reference to the newly created element.
	reference extend() { resize(size() + 1); return back(); }

	// Returns the allocator of the vector.
	Allocator &allocator() const {return *_allocator;}

	// Sets the capacity of the vector to exactly the specified amount.
	// This operation always reallocates the memory of the vector, no
	// swap trick is necessary to enforce reallocation.
	void set_capacity(unsigned capacity);

	// Trims the vector so that the capacity corresponds to its current size.
	void trim() {set_capacity(size());}

	// Finds the first occurrence of x in the vector and returns it.
	template <typename EQUATABLE> iterator find(const EQUATABLE &x) {return std::find(begin(), end(), x);}

	// Finds the first occurrence of x in the vector and returns it.
	template <typename EQUATABLE> const_iterator find(const EQUATABLE &x) const {return std::find(begin(), end(), x);}

	// Returns the index of x in the vector (or size() if it is not in the vector).
	template <typename EQUATABLE> unsigned index_of(const EQUATABLE &x) const {return (unsigned)(find(x) - begin());}

	// Returns if x is in the vector
	template <typename EQUATABLE> bool has(const EQUATABLE &x) const {return (find(x) != end());}

	// Erases the first occurrence of x in the vector.
	template <typename EQUATABLE> void erase(const EQUATABLE &item);

private:
	void move(pointer to, pointer from, ptrdiff_t n);

	void construct(pointer p, const Int2Type<true> &) {new (p) T(*_allocator);}

	void construct(pointer p, const Int2Type<false> &) {new (p) T();}

	void grow(unsigned min_capacity = 0);

private:
	unsigned		_size;
	unsigned		_capacity;
	pointer			_data;
	Allocator *		_allocator;
};

}

#include "vector.inl"
