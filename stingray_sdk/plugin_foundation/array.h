#pragma once

#include "allocator.h"
#include <algorithm>

namespace stingray_plugin_foundation {

struct NoAllocator;

// An Array<> is a simplified Vector<> for POD types that does not call
// constructors or destructors for its elements (it doesn't even zero the
// memory). It also assumes that the members can be moved and copied with
// a memmove operation and compared with memcmp.
template <class T>
class Array
{
public:
	// Type definitions

	typedef Array<T>		this_type;
	typedef T               value_type;
	typedef T*              pointer;
	typedef const T*        const_pointer;
	typedef T&              reference;
	typedef const T&        const_reference;
	typedef	pointer			iterator;
	typedef const_pointer   const_iterator;

	// Constructors

	// Creates an array that uses the specified allocator to allocate  memory.
	Array(Allocator &allocator);

	// Creates an array and presizes it to the specified size.
	Array(unsigned size, Allocator &allocator);

	// Creates an array without an allocator, one must be provided later with
	// set_allocator() before the array is resized.
	Array(const NoAllocator &);

	// Sets the allocator of the array. You can only call this before any
	// allocations have been made by the array.
	void set_allocator(Allocator &allocator);

	Array( const Array<T> &o );
	~Array() {reset();}

	// Asignment operator -- note that we do not support chained assignments.
	void operator=(const Array<T> &o);

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

	reference front() {return _data[0];}
	const_reference front() const {return _data[0];}
	reference back() {return _data[_size-1];}
	const_reference back() const {return _data[_size-1];}

	template <class ASSIGNABLE> void push_back(const ASSIGNABLE &item);
	void pop_back();

	void swap(Array<T> &o);

	template <class ASSIGNABLE> iterator insert(iterator pos, const ASSIGNABLE & x);
	iterator insert(iterator pos);
	void insert(iterator pos, const_iterator from, const_iterator to);
	iterator erase(iterator pos);
	iterator erase(iterator first, iterator last);

	void clear() {resize(0);}
	void resize(unsigned size);

	// Serializes the array to the stream.
	template <class STREAM>	void serialize(STREAM &stream);

	bool operator==(const Array<T> &o) const;
	bool operator<(const Array<T> &o) const;

	// Array extensions

	// Resets the array to initial state (no memory allocated).
	void reset() {set_capacity(0);}

	// Extends the array with the specified number of elements and returns a pointer to the first new element.
	pointer extend(unsigned elements) { resize(size() + elements); return _data + _size - elements; }

	// Extends the array with one elements and returns a reference to the newly created element.
	reference extend() { resize(size() + 1); return back(); }

	// Returns the allocator of the array.
	Allocator &allocator() const {return *_allocator;}

	// Sets the capacity of the array to exactly the specified ammount.
	// This operation always reallocates the memory of the array, no
	// swap trick is necessary to enforce reallocation.
	void set_capacity(unsigned capacity);

	// Trims the array so that the capacity corresponds to its current size.
	void trim() {set_capacity(size());}

	// Finds the first occurrence of x in the array and returns it.
	template <typename EQUATABLE> iterator find(const EQUATABLE &x) {return std::find(begin(), end(), x);}

	// Finds the first occurrence of x in the array and returns it.
	template <typename EQUATABLE> const_iterator find(const EQUATABLE &x) const {return std::find(begin(), end(), x);}

	// Returns the index of x in the array (or size() if it is not in the array).
	template <typename EQUATABLE> unsigned index_of(const EQUATABLE &x) const {return (unsigned)(find(x) - begin());}

	// Returns if x is in the array
	template <typename EQUATABLE> bool has(const EQUATABLE &x) const {return (find(x) != end());}

	// Erases the first occurrence of x in the array.
	template <typename EQUATABLE> void erase(const EQUATABLE &item);

	// "Steals" the data buffer from the array. The array will be empty after this operation. The "stealer" is
	// responsible for deallocating the stolen buffer.
	pointer steal();

private:
	void move(pointer to, pointer from, unsigned n);
	void copy(pointer to, const_pointer from, unsigned n);

	void grow(unsigned min_capacity = 0);

private:
	unsigned		_size;
	unsigned		_capacity;
	pointer			_data;
	Allocator *		_allocator;
};

} // namespace stingray_plugin_foundation

#include "array.inl"
