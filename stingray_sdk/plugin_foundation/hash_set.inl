#include "assert.h"

namespace stingray_plugin_foundation {

template<class K, class H, class E>
HashSet<K,H,E>::HashSet(Allocator &a) : _data(a), _used(0), _buckets(0),
	_spill_unused(0), _spill_freelist(END_OF_FREELIST)
{}

template<class K, class H, class E>
HashSet<K,H,E>::HashSet(unsigned buckets, unsigned spill, Allocator &a) : _data(a),
	_used(0), _buckets(buckets), _spill_unused(spill), _spill_freelist(END_OF_FREELIST)
{
	_data.resize(buckets + spill);
	for (unsigned i=0; i<_data.size(); ++i)
		_data[i].marker = UNUSED;
}

template<class K, class H, class E>
HashSet<K,H,E>::HashSet(const HashSet<K,H,E> &o) :
	_hash(o._hash), _equal(o._equal),
	_data(o._data), _used(o._used), _buckets(o._buckets),
	_spill_unused(o._spill_unused), _spill_freelist(o._spill_freelist)
{}

template<class K, class H, class E>
void HashSet<K,H,E>::operator=(const HashSet<K,H,E> &o)
{
	_hash = o._hash;
	_equal = o._equal;
	_data = o._data;
	_used = o._used;
	_buckets = o._buckets;
	_spill_unused = o._spill_unused;
	_spill_freelist = o._spill_freelist;
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
	std::swap(_hash, o._hash);
	std::swap(_equal, o._equal);
	std::swap(_data, o._data);
	std::swap(_used, o._used);
	std::swap(_buckets, o._buckets);
	std::swap(_spill_unused, o._spill_unused);
	std::swap(_spill_freelist, o._spill_freelist);
}

template<class K, class H, class E>
Allocator & HashSet<K,H,E>::allocator() const
{
	return _data.allocator();
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
	if (_data[i].marker == UNUSED)
		return END_OF_LIST;
	while (true) {
		if (i == END_OF_LIST || _equal(k, _data[i].value))
			return i;
		i = _data[i].marker;
	}
}

template<class K, class H, class E> template <class KEY_EQ>
unsigned HashSet<K,H,E>::find_or_make(const KEY_EQ &k)
{
	unsigned i = hash(k);
	if (_data[i].marker == UNUSED) {
		_data[i].marker = END_OF_LIST;
		_data[i].value = k;
		++_used;
		return i;
	}
	while (true) {
		if (_equal(k, _data[i].value) )
			return i;
		if (_data[i].marker == END_OF_LIST) {
			unsigned j = allocate_spill();
			_data[i].marker = j;
			_data[j].value = k;
			_data[j].marker = END_OF_LIST;
			return j;
		} else
			i = _data[i].marker;
	}
}

template<class K, class H, class E> template <class KEY_EQ>
void HashSet<K,H,E>::find_and_erase(const KEY_EQ &k)
{
	unsigned i = hash(k);
	if (_data[i].marker == UNUSED)
		return;

	if (_equal(k, _data[i].value)) {
		if (_data[i].marker == END_OF_LIST) {
			_data[i].marker = UNUSED;
			--_used;
		} else {
			unsigned del = _data[i].marker;
			_data[i] = _data[ del ];
			free_spill(del);
		}
		return;
	}

	unsigned prev = i;
	while (true) {
		if (_equal(k, _data[i].value) ) {
			_data[prev].marker = _data[i].marker;
			free_spill(i);
			return;
		}
		if (_data[i].marker == END_OF_LIST)
			return;
		prev = i;
		i = _data[i].marker;
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
	_spill_unused = _data.size() - _buckets;
	for (unsigned i=0; i<_data.size(); ++i)
			_data[i].marker = UNUSED;
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
	XENSURE(new_buckets > _used);
	unsigned spill = int(new_buckets * 0.37f + 1);
	this_type new_hash(new_buckets, spill, _data.allocator());
	clear_freelist();
	for (unsigned i=0; i<_data.size(); ++i) {
		if (_data[i].marker != UNUSED)
			new_hash.insert(_data[i].value);
	}
	swap(new_hash);
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
	return _data.size();
}

template<class K, class H, class E>
bool HashSet<K,H,E>::bucket_valid(unsigned i) const
{
	return (_data[i].marker & 0x80000000) == 0;
}

template<class K, class H, class E>
const typename HashSet<K,H,E>::key_type &HashSet<K,H,E>::bucket_value(unsigned i) const
{
	return _data[i].value;
}

template<class K, class H, class E>
typename HashSet<K,H,E>::key_type &HashSet<K,H,E>::bucket_value(unsigned i)
{
	return _data[i].value;
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
		_spill_freelist = _data[i].marker;
		return i;
	} else {
		XENSURE(_spill_unused > 0);
		i = _data.size() - _spill_unused;
		--_spill_unused;
	}
	_data[i].marker = UNUSED;
	return i;
}

template<class K, class H, class E>
void HashSet<K,H,E>::free_spill(unsigned i)
{
	--_used;
	_data[i].marker = _spill_freelist;
	_spill_freelist = i | 0x80000000;
}

template<class K, class H, class E>
void HashSet<K,H,E>::clear_freelist()
{
	while (_spill_freelist != END_OF_FREELIST) {
		unsigned i = _spill_freelist & 0x7fffffff;
		_spill_freelist = _data[i].marker;
		_data[i].marker = UNUSED;
	}
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
			key_type k(_data.allocator());
			stream & k;
			insert(k);
		}
	}
}

} // namespace stingray_plugin_foundation
