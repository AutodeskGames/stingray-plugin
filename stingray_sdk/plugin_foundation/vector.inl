namespace stingray_plugin_foundation {

template <class T> Vector<T>::Vector(Allocator &allocator) : _size(0), _capacity(0), _data(0), _allocator(&allocator)
{
}

template <class T> Vector<T>::Vector(unsigned size, Allocator &allocator) : _size(0), _capacity(0), _data(0), _allocator(&allocator)
{
	resize(size);
}

template <class T> Vector<T>::Vector(const NoAllocator &) : _size(0), _capacity(0), _data(0), _allocator(0)
{
}

template <class T> void Vector<T>::set_allocator(Allocator &allocator)
{
	_allocator = &allocator;
}

template <class T> Vector<T>::Vector( const Vector<T> &o ) : _size(0), _capacity(0), _data(0), _allocator(o._allocator)
{
	set_capacity(o.size());
	for (unsigned i=0; i<o.size(); ++i) {
		construct(_data + i, IS_ALLOCATOR_AWARE_TYPE(T)());
		_data[i] = o[i];
	}
	_size = o.size();
}

template <class T> void Vector<T>::operator=(const Vector<T> &o)
{
	resize(o.size());
	for (unsigned i=0; i<_size; ++i)
		_data[i] = o[i];
}

template <class T> typename Vector<T>::reference Vector<T>::operator[](unsigned i) {
	#if defined(_DEBUG)
		XASSERT(i < _size, "Vector index out of bounds %d >= %d", i, _size);
	#endif
	return _data[i];
}
template <class T> typename Vector<T>::const_reference Vector<T>::operator[](unsigned i) const {
	#if defined(_DEBUG)
		XASSERT(i < _size, "Vector index out of bounds %d >= %d", i, _size);
	#endif
	return _data[i];
}

template <class T> void Vector<T>::reserve(unsigned capacity)
{
	if (capacity > _capacity)
		grow(capacity);
}

template <class T> template <class ASSIGNABLE>
void Vector<T>::push_back(const ASSIGNABLE &item)
{
	if (_size + 1 > _capacity)
		grow();
	construct(_data + _size, IS_ALLOCATOR_AWARE_TYPE(T)());
	#pragma warning(push)
	#pragma warning(disable:4244) // can't fix cast warning
	_data[_size] = item;
	#pragma warning(pop)
	++_size;
}

template <class T> void Vector<T>::pop_back()
{
	_size--;
	_data[_size].~T();
}

template <class T> void Vector<T>::swap(Vector<T> &o)
{
	XENSURE(_allocator == o._allocator);
	std::swap(_size, o._size);
	std::swap(_capacity, o._capacity);
	std::swap(_data, o._data);
	std::swap(_allocator, o._allocator);
}

template <class T> template <class ASSIGNABLE>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const ASSIGNABLE& x)
{
	if (_size + 1 > _capacity) {
		unsigned i = (unsigned)(pos - _data);
		grow();
		pos = _data + i;
	}
	move(pos + 1, pos, (_data + _size) - pos);
	construct(pos, IS_ALLOCATOR_AWARE_TYPE(T)());
	*pos = x;
	++_size;
	return pos;
}

template <class T> typename Vector<T>::iterator Vector<T>::insert(iterator pos)
{
	if (_size + 1 > _capacity) {
		unsigned i = (unsigned)(pos - _data);
		grow();
		pos = _data + i;
	}
	move(pos + 1, pos, (_data + _size) - pos);
	construct(pos, IS_ALLOCATOR_AWARE_TYPE(T)());
	++_size;
	return pos;
}

template <class T> void Vector<T>::insert(iterator pos, const_iterator from, const_iterator to)
{
	unsigned add = (unsigned)(to - from);
	if (_size + add > _capacity) {
		unsigned i = (unsigned)(pos - _data);
		grow(_size + add);
		pos = _data + i;
	}
	move(pos + add, pos, (_data + _size) - pos);
	while (from < to) {
		construct(pos, IS_ALLOCATOR_AWARE_TYPE(T)());
		*pos = *from;
		++pos;
		++from;
		++_size;
	}
}

template <class T> typename Vector<T>::iterator Vector<T>::erase(iterator pos)
{
	#if defined(_DEBUG)
		XASSERT(pos >= begin() && pos < end(), "Trying to remove outside vector.");
	#endif
	pos->~T();
	move(pos, pos + 1, (_data + _size) - pos - 1);
	--_size;
	return pos;
}

template <class T> typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last)
{
	#if defined(_DEBUG)
		XASSERT(first <= last, "Trying to remove inverted range from vector.");
		XASSERT(first >= begin() && last <= end(), "Trying to remove range outside vector.");
	#endif
	for (iterator p = first; p < last; ++p)
		p->~T();
	move(first, last, (_data + _size) - last);
	_size -= (unsigned)(last - first);
	return first;
}

template <class T> template <typename EQUATABLE> void Vector<T>::erase(const EQUATABLE &item)
{
	iterator it = find(item);
	#if defined(_DEBUG)
		XASSERT(it != end(), "Trying to remove nonexisting value in vector.");
	#endif
	erase(it);
}

template <class T> void Vector<T>::resize(unsigned size)
{
	if (size > _capacity)
		grow(size);

	while (size > _size) {
		construct(_data + _size, IS_ALLOCATOR_AWARE_TYPE(T)());
		++_size;
	}

	while (_size > size) {
		--_size;
		_data[_size].~T();
	}
}

template <class T> void Vector<T>::set_capacity(unsigned capacity)
{
	if (capacity == _capacity)
		return;

	if (capacity < _size)
		resize(capacity);

	pointer new_data = 0;

	if (capacity > 0) {
		new_data = (pointer)_allocator->allocate(sizeof(value_type)*capacity, math::max((int)alignof(value_type), 4));
		move(new_data, _data, _size);
	}
	_allocator->deallocate(_data);

	_data = new_data;
	_capacity = capacity;
}

template <class T> void Vector<T>::move(pointer to, pointer from, ptrdiff_t n)
{
	memmove(to, from, sizeof(T) * n);
}

template <class T>
template <class STREAM> void Vector<T>::serialize(STREAM &stream)
{
	unsigned sz = size();
	stream & sz;
	resize(sz);
	for (unsigned i=0; i<sz; ++i)
		stream & (*this)[i];
}

template<class T> bool Vector<T>::operator==(const Vector<T> &o) const
{
	if (size() != o.size())
		return false;
	for (unsigned i=0; i<size(); ++i)
		if ((*this)[i] != o[i])
			return false;
	return true;
}

template<class T> bool Vector<T>::operator<(const Vector<T> &o) const
{
	if (size() != o.size())
		return size() < o.size();
	for (unsigned i=0; i<size(); ++i)
		if ((*this)[i] != o[i])
			return (*this)[i] < o[i];
	return false;
}

template <class T> void Vector<T>::grow(unsigned min_capacity)
{
	uint64_t new_capacity = (uint64_t)_capacity*2 + 10;
	if (new_capacity < min_capacity)
		new_capacity = min_capacity;
	else if (new_capacity > UINT32_MAX)
		new_capacity = UINT32_MAX;
	set_capacity((unsigned)new_capacity);
}

}
