#include "assert.h"

namespace stingray_plugin_foundation {

template <class T> Array<T>::Array(Allocator &allocator) : _size(0), _capacity(0), _data(0), _allocator(&allocator)
{
}

template <class T> Array<T>::Array(unsigned size, Allocator &allocator) : _size(0), _capacity(0), _data(0), _allocator(&allocator)
{
	resize(size);
}

template <class T> Array<T>::Array(const NoAllocator &) : _size(0), _capacity(0), _data(0), _allocator(0)
{
}

template <class T> void Array<T>::set_allocator(Allocator &allocator)
{
	_allocator = &allocator;
}

template <class T> Array<T>::Array( const Array<T> &o ) : _size(0), _capacity(0), _data(0), _allocator(o._allocator)
{
	set_capacity(o.size());
	copy(_data, o._data, o.size());
	_size = o.size();
}

template <class T> void Array<T>::operator=(const Array<T> &o)
{
	resize(o.size());
	copy(_data, o._data, o.size());
}

template <class T> typename Array<T>::reference Array<T>::operator[](unsigned i) {
	#if defined(_DEBUG)
		XENSURE(i < _size);
	#endif
	return _data[i];
}
template <class T> typename Array<T>::const_reference Array<T>::operator[](unsigned i) const {
	#if defined(_DEBUG)
		XENSURE(i < _size);
	#endif
	return _data[i];
}

template <class T> void Array<T>::reserve(unsigned capacity)
{
	if (capacity > _capacity)
		grow(capacity);
}

template <class T> template <class ASSIGNABLE>
void Array<T>::push_back(const ASSIGNABLE &item)
{
	if (_size + 1 > _capacity)
		grow();
	_data[_size++] = item;
}

template <class T> void Array<T>::pop_back()
{
	_size--;
}

template <class T> void Array<T>::swap(Array<T> &o)
{
	{unsigned temp = _size; _size = o._size; o._size = temp;}
	{unsigned temp = _capacity; _capacity = o._capacity; o._capacity = temp;}
	{pointer temp = _data; _data = o._data; o._data = temp;}
	{Allocator *temp = _allocator; _allocator = o._allocator; o._allocator = temp;}
}

template <class T> template <class ASSIGNABLE>
typename Array<T>::iterator Array<T>::insert(iterator pos, const ASSIGNABLE& x)
{
	if (_size + 1 > _capacity) {
		unsigned i = (unsigned)(pos - _data);
		grow();
		pos = _data + i;
	}
	move(pos + 1, pos, (unsigned)((_data + _size) - pos));
	*pos = x;
	++_size;
	return pos;
}

template <class T> typename Array<T>::iterator Array<T>::insert(iterator pos)
{
	if (_size + 1 > _capacity) {
		unsigned i = pos - _data;
		grow();
		pos = _data + i;
	}
	move(pos + 1, pos, (_data + _size) - pos);
	++_size;
	return pos;
}

template <class T> void Array<T>::insert(iterator pos, const_iterator from, const_iterator to)
{
	unsigned add = (unsigned)(to - from);
	if (_size + add > _capacity) {
		size_t i = pos - _data;
		grow(_size + add);
		pos = _data + i;
	}
	move(pos + add, pos, (unsigned)((_data + _size) - pos));
	copy(pos, from, add);
	_size += add;
}

template <class T> typename Array<T>::iterator Array<T>::erase(iterator pos)
{
	move(pos, pos + 1, (unsigned)((_data + _size) - pos - 1));
	--_size;
	return pos;
}

template <class T> typename Array<T>::iterator Array<T>::erase(iterator first, iterator last)
{
	move(first, last, (unsigned)((_data + _size) - last));
	_size -= (unsigned)(last - first);
	return first;
}

template <class T> void Array<T>::resize(unsigned size)
{
	if (size > _capacity)
		grow(size);

	_size = size;
}

template <class T> void Array<T>::set_capacity(unsigned capacity)
{
	if (capacity == _capacity)
		return;

	if (capacity < _size)
		resize(capacity);

	pointer new_data = 0;

	if (capacity > 0) {
		unsigned align = alignof(value_type) > 4 ? alignof(value_type) : 4;
		new_data = (pointer)_allocator->allocate(sizeof(value_type)*capacity, align);
		copy(new_data, _data, _size);
	}
	_allocator->deallocate(_data);

	_data = new_data;
	_capacity = capacity;
}

template <class T> void Array<T>::move(pointer to, pointer from, unsigned n)
{
	memmove(to, from, sizeof(T) * n);
}

template <class T> void Array<T>::copy(pointer to, const_pointer from, unsigned n)
{
	memcpy(to, from, sizeof(T) * n);
}

template <class T>
template <class STREAM> void Array<T>::serialize(STREAM &stream)
{
	unsigned sz = size();
	stream & sz;
	resize(sz);
	for (unsigned i=0; i<sz; ++i)
		stream & (*this)[i];
}

template<class T> bool Array<T>::operator==(const Array<T> &o) const
{
	if (size() != o.size())
		return false;
	return memcmp(_data, o._data, sizeof(T)*size()) == 0;
}

template<class T> bool Array<T>::operator<(const Array<T> &o) const
{
	if (size() != o.size())
		return size() < o.size();
	return memcmp(_data, o._data, sizeof(T)*size()) < 0;
}

template <class T> void Array<T>::grow(unsigned min_capacity)
{
	uint64_t new_capacity = (uint64_t)_capacity*2 + 10;
	if (new_capacity < min_capacity)
		new_capacity = min_capacity;
	else if (new_capacity > UINT32_MAX)
		new_capacity = UINT32_MAX;
	set_capacity((unsigned)new_capacity);
}

template <class T> typename Array<T>::pointer Array<T>::steal()
{
	pointer return_value = _data;
	_data = 0;
	_capacity = 0;
	_size = 0;
	return return_value;
}

} // namespace stingray_plugin_foundation
