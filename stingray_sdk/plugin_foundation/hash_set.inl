#include "assert.h"

namespace stingray_plugin_foundation {

template<class K, class H, class E>
HashSet<K,H,E>::HashSet(Allocator &a) : _data(), _used(0), _buckets(0),
	_spill_unused(0), _spill_freelist(END_OF_FREELIST), _allocator(a)
{}

template<class K, class H, class E>
HashSet<K,H,E>::HashSet(unsigned buckets, unsigned spill, Allocator &a) : _data(),
	_used(0), _buckets(buckets), _spill_unused(spill), _spill_freelist(END_OF_FREELIST)
	, _allocator(a)
{
	allocate_data(buckets + spill);
	for (unsigned i=0; i<_data.size; ++i)
		_data.marker[i] = UNUSED;
}

template<class K, class H, class E>
HashSet<K,H,E>::HashSet(const HashSet<K,H,E> &o) :
	_hash(o._hash), _equal(o._equal),
	_data(), _used(o._used), _buckets(o._buckets),
	_spill_unused(o._spill_unused), _spill_freelist(o._spill_freelist),
	_allocator(o._allocator)
{
	allocate_data(o._data.size);
	for (unsigned i = 0; i < _data.size; ++i) {
		if (o._data.marker[i] != UNUSED && (o._data.marker[i] & 0x80000000) == 0) {
			construct(_data.key[i], IS_ALLOCATOR_AWARE_TYPE(K)());
			_data.key[i] = o._data.key[i];
		}
		_data.marker[i] = o._data.marker[i];
	}
}

template<class K, class H, class E>
void HashSet<K,H,E>::operator=(const HashSet<K,H,E> &o)
{
	if (this == &o)
		return;
	clear();
	_hash = o._hash;
	_equal = o._equal;
	_allocator.deallocate(_data.marker);
	_data.marker = nullptr;
	allocate_data(o._data.size);
	for (unsigned i = 0; i < _data.size; ++i) {
		if (o._data.marker[i] != UNUSED && (o._data.marker[i] & 0x80000000) == 0) {
			construct(_data.key[i], IS_ALLOCATOR_AWARE_TYPE(K)());
			_data.key[i] = o._data.key[i];
		}
		_data.marker[i] = o._data.marker[i];
	}
	_used = o._used;
	_buckets = o._buckets;
	_spill_unused = o._spill_unused;
	_spill_freelist = o._spill_freelist;
}

template<class K, class H, class E>
HashSet<K, H, E>::~HashSet()
{
	clear();
	_allocator.deallocate(_data.marker);
}

template <class K, class H, class E>
void HashSet<K,H,E>::reserve(unsigned items)
{
	unsigned buckets = int(items * 1.37f);
	if (buckets < int(19*1.37f))
		buckets = int(19*1.37f);
	rehash(buckets);
}

template<class K, class H, class E>
void HashSet<K,H,E>::swap(HashSet<K,H,E> &o)
{
	XENSURE(&_allocator == &o._allocator);
	std::swap(_hash, o._hash);
	std::swap(_equal, o._equal);
	std::swap(_data.size, o._data.size);
	std::swap(_data.marker, o._data.marker);
	std::swap(_data.key, o._data.key);
	std::swap(_used, o._used);
	std::swap(_buckets, o._buckets);
	std::swap(_spill_unused, o._spill_unused);
	std::swap(_spill_freelist, o._spill_freelist);
}

template<class K, class H, class E>
Allocator & HashSet<K,H,E>::allocator() const
{
	return _allocator;
}

template<class K, class H, class E>
unsigned HashSet<K,H,E>::size() const
{
	return _used;
}

template<class K, class H, class E>
bool HashSet<K,H,E>::empty() const
{
	return _used == 0;
}

template<class K, class H, class E> template <class KEY_EQ>
unsigned HashSet<K,H,E>::find_or_fail(const KEY_EQ &k) const
{
	if (empty())
		return END_OF_LIST;

	unsigned i = hash(k);
	if (_data.marker[i] == UNUSED)
		return END_OF_LIST;
	while (true) {
		if (i == END_OF_LIST || _equal(k, _data.key[i]))
			return i;
		i = _data.marker[i];
	}
}

template<class K, class H, class E> template <class KEY_EQ>
unsigned HashSet<K,H,E>::find_or_make(const KEY_EQ &k)
{
	unsigned i = hash(k);
	if (_data.marker[i] == UNUSED) {
		++_used;
		construct(_data.key[i], IS_ALLOCATOR_AWARE_TYPE(K)());
		_data.key[i] = k;
		_data.marker[i] = END_OF_LIST;
		return i;
	}
	while (true) {
		if (_equal(k, _data.key[i]) )
			return i;

		if (_data.marker[i] == END_OF_LIST) {
			unsigned j = allocate_spill();
			_data.marker[i] = j;
			i = j;
			construct(_data.key[i], IS_ALLOCATOR_AWARE_TYPE(K)());
			_data.key[i] = k;
			_data.marker[i] = END_OF_LIST;
			return j;
		} else
			i = _data.marker[i];
	}
}

template<class K, class H, class E> template <class KEY_EQ>
void HashSet<K,H,E>::find_and_erase(const KEY_EQ &k)
{
	unsigned i = hash(k);
	if (_data.marker[i] == UNUSED)
		return;

	if (_equal(k, _data.key[i])) {
		if (_data.marker[i] == END_OF_LIST) {
			_data.marker[i] = UNUSED;
			destruct(_data.key[i]);
			--_used;
		} else {
			unsigned del = _data.marker[i];
			_data.marker[i] = _data.marker[del];
			_data.key[i] = _data.key[del];
			destruct(_data.key[del]);
			free_spill(del);
		}
		return;
	}

	unsigned prev = i;
	while (true) {
		if (_equal(k, _data.key[i]) ) {
			_data.marker[prev] = _data.marker[i];
			destruct(_data.key[i]);
			free_spill(i);
			return;
		}

		if (_data.marker[i] == END_OF_LIST)
			return;

		prev = i;
		i = _data.marker[i];
	}
}

template<class K, class H, class E> template <class KEY_EQ>
bool HashSet<K,H,E>::has(const KEY_EQ &k) const
{
	return find_or_fail(k) != END_OF_LIST;
}

template<class K, class H, class E>
void HashSet<K,H,E>::clear()
{
	_used = 0;
	_spill_freelist = END_OF_FREELIST;
	_spill_unused = _data.size - _buckets;
	for (unsigned i = 0; i<_data.size; ++i) {
		if (bucket_valid(i))
			destruct(_data.key[i]);
		_data.marker[i] = UNUSED;
	}
}

template<class K, class H, class E> template <class KEY_EQ>
void HashSet<K,H,E>::insert(const KEY_EQ &k)
{
	if (full()) {
		unsigned i = find_or_fail(k);
		if (i != END_OF_LIST)
			return;
		grow();
	}
	find_or_make(k);
}

template<class K, class H, class E> template <class KEY_EQ>
void HashSet<K,H,E>::erase(const KEY_EQ &k)
{
	find_and_erase(k);
}

template<class K, class H, class E>
void HashSet<K,H,E>::rehash(unsigned new_buckets)
{
	XENSURE(new_buckets >= _used);
	clear_freelist();
	unsigned spill = int(new_buckets * 0.37f + 1);
	unsigned old_size = _data.size;
	if (_data.size == 0) {
		allocate_data(new_buckets + spill);
		_buckets = new_buckets;
		_spill_unused = spill;
		for (unsigned i = 0; i<_data.size; ++i)
			_data.marker[i] = UNUSED;
		return;
	}
	this_type new_set(new_buckets, spill, _allocator);
	for (unsigned o = 0; o<old_size; ++o) {
		if (_data.marker[o] == UNUSED) {
			continue;
		}
		// Find/allocate entry
		auto &k = _data.key[o];
		unsigned i = new_set.hash(k);
		if (new_set._data.marker[i] == UNUSED) {
			new_set._data.marker[i] = END_OF_LIST;
			++new_set._used;
		}
		else {
			// Walk the hash chain until the end and add a new entry
			while (new_set._data.marker[i] != END_OF_LIST)
				i = new_set._data.marker[i];

			unsigned j = new_set.allocate_spill();
			new_set._data.marker[i] = j;
			i = j;
			new_set._data.marker[i] = END_OF_LIST;
		}
		memmove(&new_set._data.key[i], &k, sizeof(K));
		_data.marker[o] = UNUSED;
	}
	swap(new_set);
}

template<class K, class H, class E>
typename HashSet<K,H,E>::const_iterator HashSet<K,H,E>::begin() const
{
	return const_iterator(*this, 0);
}

template<class K, class H, class E>
typename HashSet<K,H,E>::const_iterator HashSet<K,H,E>::end() const
{
	return const_iterator(*this, num_buckets());
}

template<class K, class H, class E>
unsigned HashSet<K,H,E>::num_buckets() const
{
	return _data.size;
}

template<class K, class H, class E>
bool HashSet<K,H,E>::bucket_valid(unsigned i) const
{
	return (_data.marker[i] & 0x80000000) == 0;
}

template<class K, class H, class E>
const typename HashSet<K,H,E>::key_type &HashSet<K,H,E>::bucket_value(unsigned i) const
{
	return _data.key[i];
}

template<class K, class H, class E>
typename HashSet<K,H,E>::key_type &HashSet<K,H,E>::bucket_value(unsigned i)
{
	return _data.key[i];
}

template<class K, class H, class E>
bool HashSet<K,H,E>::full() const
{
	return _spill_unused == 0 && _spill_freelist == END_OF_FREELIST;
}

template<class K, class H, class E>
void HashSet<K,H,E>::grow()
{
	do {
		unsigned new_buckets = _buckets * 2 + 1;
		if (new_buckets < 19)
			new_buckets = 19;
		rehash(new_buckets);
	} while (full());
}

template<class K, class H, class E> template <class KEY_EQ>
unsigned HashSet<K,H,E>::hash(const KEY_EQ &k) const
{
	return _hash(k) % _buckets;
}

template<class K, class H, class E>
unsigned HashSet<K,H,E>::allocate_spill()
{
	++_used;
	unsigned i = 0;
	if (_spill_freelist != END_OF_FREELIST) {
		i = _spill_freelist & 0x7fffffff;
		_spill_freelist = _data.marker[i];
		return i;
	} else {
		XENSURE(_spill_unused > 0);
		i = _data.size - _spill_unused;
		--_spill_unused;
	}
	_data.marker[i] = UNUSED;
	return i;
}

template<class K, class H, class E>
void HashSet<K,H,E>::free_spill(unsigned i)
{
	--_used;
	_data.marker[i] = _spill_freelist;
	_spill_freelist = i | 0x80000000;
}

template<class K, class H, class E>
void HashSet<K,H,E>::clear_freelist()
{
	while (_spill_freelist != END_OF_FREELIST) {
		unsigned i = _spill_freelist & 0x7fffffff;
		_spill_freelist = _data.marker[i];
		_data.marker[i] = UNUSED;
	}
}

template<class K, class H, class E>
void HashSet<K, H, E>::allocate_data(unsigned count)
{
	XASSERT(_data.marker == nullptr, "Data must be deallocated/cleared before allocating new data");
	if (count == 0) {
		_data = Data();
		return;
	}

	auto marker_size = (((sizeof(unsigned) * count) + sizeof(void*) - 1) / sizeof(void*)) * sizeof(void*);
	auto key_size = sizeof(key_type) * count;
	auto data_size = marker_size + key_size;
	_data.marker = (unsigned*)_allocator.allocate(data_size);
	_data.key = (key_type*)&(((char*)_data.marker)[marker_size]);
	_data.size = count;
}

template<class K, class H, class E>
template <class STREAM> void HashSet<K,H,E>::serialize(STREAM &stream)
{
	unsigned n = _used;
	stream & n;
	if (stream.is_output()) {
		iterator it(*this, 0);
		iterator end(*this, num_buckets());
		for (; it != end; ++it)
			stream & *it;
	} else {
		for (unsigned i=0; i<n; ++i) {
			key_type k(_allocator);
			stream & k;
			insert(k);
		}
	}
}

} // namespace stingray_plugin_foundation
