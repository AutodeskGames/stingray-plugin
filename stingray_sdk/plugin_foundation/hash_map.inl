namespace stingray_plugin_foundation {

template <class K, class D, class H, class E>
HashMap<K,D,H,E>::HashMap(Allocator &a) : _data(a), _used(0), _buckets(0),
	_spill_unused(0), _spill_freelist(END_OF_FREELIST)
{}

template <class K, class D, class H, class E>
HashMap<K,D,H,E>::HashMap(unsigned buckets, unsigned spill, Allocator &a) : _data(a),
	_used(0), _buckets(buckets), _spill_unused(spill), _spill_freelist(END_OF_FREELIST)
{
	_data.resize(buckets + spill);
	for (unsigned i=0; i<_data.size(); ++i)
		_data[i].marker = UNUSED;
}

template <class K, class D, class H, class E>
HashMap<K,D,H,E>::HashMap(const HashMap<K,D,H,E> &o) :
	_hash(o._hash), _equal(o._equal),
	_data(o._data), _used(o._used), _buckets(o._buckets),
	_spill_unused(o._spill_unused), _spill_freelist(o._spill_freelist)
{}

template <class K, class D, class H, class E>
void HashMap<K,D,H,E>::operator=(const HashMap<K,D,H,E> &o)
{
	_hash = o._hash;
	_equal = o._equal;
	_data = o._data;
	_used = o._used;
	_buckets = o._buckets;
	_spill_unused = o._spill_unused;
	_spill_freelist = o._spill_freelist;
}

template <class K, class D, class H, class E>
void HashMap<K,D,H,E>::swap(HashMap<K,D,H,E> &o)
{
	std::swap(_hash, o._hash);
	std::swap(_equal, o._equal);
	_data.swap(o._data);
	std::swap(_used, o._used);
	std::swap(_buckets, o._buckets);
	std::swap(_spill_unused, o._spill_unused);
	std::swap(_spill_freelist, o._spill_freelist);
}

template <class K, class D, class H, class E>
typename HashMap<K,D,H,E>::iterator HashMap<K,D,H,E>::begin()
{
	return iterator(*this, 0);
}

template <class K, class D, class H, class E>
typename HashMap<K,D,H,E>::iterator HashMap<K,D,H,E>::end()
{
	return iterator(*this, num_buckets());
}

template <class K, class D, class H, class E>
typename HashMap<K,D,H,E>::const_iterator HashMap<K,D,H,E>::begin() const
{
	return const_iterator(*this, 0);
}

template <class K, class D, class H, class E>
typename HashMap<K,D,H,E>::const_iterator HashMap<K,D,H,E>::end() const
{
	return const_iterator(*this, num_buckets());
}

template <class K, class D, class H, class E> template <class KEY_EQ>
typename HashMap<K,D,H,E>::const_iterator HashMap<K,D,H,E>::find(const KEY_EQ &k) const{
	auto i = find_or_fail(k);
	return (i == END_OF_LIST) ? end() : const_iterator(*this, i);
}

template <class K, class D, class H, class E> template <class KEY_EQ>
typename HashMap<K,D,H,E>::iterator HashMap<K,D,H,E>::find(const KEY_EQ &k){
	auto i = find_or_fail(k);
	return (i == END_OF_LIST) ? end() : iterator(*this, i);
}

template <class K, class D, class H, class E>
Allocator & HashMap<K,D,H,E>::allocator() const
{
	return _data.allocator();
}

template <class K, class D, class H, class E>
unsigned HashMap<K,D,H,E>::size() const
{
	return _used;
}

template <class K, class D, class H, class E>
bool HashMap<K,D,H,E>::empty() const
{
	return _used == 0;
}

template <class K, class D, class H, class E> template <class KEY_EQ>
bool HashMap<K,D,H,E>::has(const KEY_EQ &k) const
{
	return find_or_fail(k) != END_OF_LIST;
}

template <class K, class D, class H, class E> template <class KEY_EQ>
typename HashMap<K,D,H,E>::data_type &HashMap<K,D,H,E>::operator[](const KEY_EQ &k)
{
	if (full()) {
		unsigned i = find_or_fail(k);
		if (i != END_OF_LIST)
			return _data[i].value.second;
		grow();
	}
	return _data[find_or_make(k)].value.second;
}

template <class K, class D, class H, class E> template <class KEY_EQ>
const typename HashMap<K,D,H,E>::data_type &HashMap<K,D,H,E>::operator[](const KEY_EQ &k) const
{
	unsigned i = find_or_fail(k);
	XASSERT(i != END_OF_LIST, "key not in map");
	return _data[i].value.second;
}

template <class K, class D, class H, class E> template <class KEY_EQ>
typename HashMap<K,D,H,E>::data_type &HashMap<K,D,H,E>::get(const KEY_EQ &k, data_type &def)
{
	unsigned i = find_or_fail(k);
	if (i == END_OF_LIST)
		return def;
	else
		return _data[i].value.second;
}

template <class K, class D, class H, class E> template <class KEY_EQ>
const typename HashMap<K,D,H,E>::data_type &HashMap<K,D,H,E>::get(const KEY_EQ &k, const data_type &def) const
{
	unsigned i = find_or_fail(k);
	if (i == END_OF_LIST)
		return def;
	else
		return _data[i].value.second;
}

template <class K, class D, class H, class E>
void HashMap<K,D,H,E>::clear()
{
	_used = 0;
	_spill_freelist = END_OF_FREELIST;
	_spill_unused = _data.size() - _buckets;
	for (unsigned i=0; i<_data.size(); ++i) {
		if (bucket_valid(i))
			_data[i].value = value_type(_data.allocator());
		_data[i].marker = UNUSED;
	}
}

template <class K, class D, class H, class E> template <class KEY_EQ, class DATA_EQ>
void HashMap<K,D,H,E>::insert(const KEY_EQ &k, const DATA_EQ &v)
{
	(*this)[k] = v;
}

template <class K, class D, class H, class E> template <class KEY_EQ>
void HashMap<K,D,H,E>::erase(const KEY_EQ &k)
{
	find_and_erase(k);
}

template <class K, class D, class H, class E>
void HashMap<K,D,H,E>::rehash(unsigned new_buckets)
{
	XENSURE(new_buckets >= _used);
	unsigned spill = int(new_buckets * 0.37f + 1);
	this_type new_hash(new_buckets, spill, _data.allocator());
	clear_freelist();
	for (unsigned i=0; i<_data.size(); ++i) {
		if (_data[i].marker != UNUSED)
			new_hash.insert(_data[i].value.first, _data[i].value.second);
	}
	swap(new_hash);
}

template <class K, class D, class H, class E>
void HashMap<K,D,H,E>::reserve(unsigned items)
{
	unsigned buckets = int(items * 1.37f);
	if (buckets < 26)
		buckets = 26;
	rehash(buckets);
}

template <class K, class D, class H, class E>
unsigned HashMap<K,D,H,E>::num_buckets() const
{
	return _data.size();
}

template <class K, class D, class H, class E>
bool HashMap<K,D,H,E>::bucket_valid(unsigned i) const
{
	return (_data[i].marker & 0x80000000) == 0;
}

template <class K, class D, class H, class E>
typename HashMap<K,D,H,E>::value_type &HashMap<K,D,H,E>::bucket_value(unsigned i)
{
	return _data[i].value;
}

template <class K, class D, class H, class E>
const typename HashMap<K,D,H,E>::value_type &HashMap<K,D,H,E>::bucket_value(unsigned i) const
{
	return _data[i].value;
}

// Searches for `k` in the map. Returns the index of the entry if found and
// END_OF_LIST if not found.
template <class K, class D, class H, class E> template <class KEY_EQ>
unsigned HashMap<K,D,H,E>::find_or_fail(const KEY_EQ &k) const
{
	// Is hash empty?
	if (empty())
		return END_OF_LIST;

	unsigned i = hash(k);

	// Is primary slot unused?
	if (_data[i].marker == UNUSED)
		return END_OF_LIST;

	// Walk the hash chain until key matches or end is reached.
	while (true) {
		if (i == END_OF_LIST || _equal(k, _data[i].value.first))
			return i;
		i = _data[i].marker;
	}
}

// Searches for `k` in the map. Returns the index if it is found. If it is
// not found a new hash slot is create for `k` and its index is returned.
template <class K, class D, class H, class E> template <class KEY_EQ>
unsigned HashMap<K,D,H,E>::find_or_make(const KEY_EQ &k)
{
	unsigned i = hash(k);

	// Is primary slot unused?
	if (_data[i].marker == UNUSED) {
		_data[i].marker = END_OF_LIST;
		_data[i].value.first = k;
		++_used;
		return i;
	}

	while (true) {
		// Walk the hash chain until found
		if (_equal(k, _data[i].value.first) )
			return i;

		// Or until end of hash chain, in which case we add a new entry
		// to the end.
		if (_data[i].marker == END_OF_LIST) {
			unsigned j = allocate_spill();
			_data[i].marker = j;
			_data[j].value.first = k;
			_data[j].marker = END_OF_LIST;
			return j;
		}

		i = _data[i].marker;
	}
}

// Searches for `k` in the map. If it is found, it is erased.
template <class K, class D, class H, class E> template <class KEY_EQ>
void HashMap<K,D,H,E>::find_and_erase(const KEY_EQ &k)
{
	// early out to avoid division by zero in hash method if the map is empty.
	if (_buckets == 0)
		return;

	unsigned i = hash(k);

	// Is primary slot unused?
	if (_data[i].marker == UNUSED)
		return;

	// Did the primary slot match?
	if (_equal(k, _data[i].value.first)) {
		// If there is no chain, just return the primary value
		if (_data[i].marker == END_OF_LIST) {
			_data[i].marker = UNUSED;
			_data[i].value = value_type(_data.allocator());
			--_used;
		// If there is a chain, bring in the first value from the
		// chain and mark it as free in the spillover region.
		} else {
			unsigned del = _data[i].marker;
			_data[i] = _data[ del ];
			_data[del].value = value_type(_data.allocator());
			free_spill(del);
		}
		return;
	}

	// If not, search the hash chain for a match
	unsigned prev = i;
	while (true) {
		// If there is a match remove that value from the chain and
		// mark it as free in the spillover region.
		if (_equal(k, _data[i].value.first) ) {
			_data[prev].marker = _data[i].marker;
			_data[i].value = value_type(_data.allocator());
			free_spill(i);
			return;
		}

		// If end of chain was reached without finding the key just return
		if (_data[i].marker == END_OF_LIST)
			return;

		prev = i;
		i = _data[i].marker;
	}
}

template <class K, class D, class H, class E>
bool HashMap<K,D,H,E>::full() const
{
	// Hash map is full when spillover region is full
	return _spill_unused == 0 && _spill_freelist == END_OF_FREELIST;
}

template <class K, class D, class H, class E>
void HashMap<K,D,H,E>::grow()
{
	do {
		unsigned new_buckets = _buckets * 2 + 1;
		if (new_buckets < 19)
			new_buckets = 19;
		rehash(new_buckets);
	} while (full());
}

template <class K, class D, class H, class E> template <class KEY_EQ>
unsigned HashMap<K,D,H,E>::hash(const KEY_EQ &k) const
{
	XENSURE(_buckets > 0);

	return _hash(k) % _buckets;
}

// Allocate a slot in the spillover region and return it.
template <class K, class D, class H, class E>
unsigned HashMap<K,D,H,E>::allocate_spill()
{
	++_used;

	// If there spillover free list is non-empty, use its
	// first item.
	if (_spill_freelist != END_OF_FREELIST) {
		unsigned i = _spill_freelist & 0x7fffffff;
		_spill_freelist = _data[i].marker;
		return i;
	}

	// Return the first unused item from the spillover region.
	XENSURE(_spill_unused > 0);
	unsigned i = _data.size() - _spill_unused;
	--_spill_unused;
	_data[i].marker = UNUSED;
	return i;
}

template <class K, class D, class H, class E>
void HashMap<K,D,H,E>::free_spill(unsigned i)
{
	// Free a spillover item by inserting it in the freelist.
	--_used;
	_data[i].marker = _spill_freelist;
	_spill_freelist = i | 0x80000000;
}

// Clears the spillover freelist (marks all items as unused).
template <class K, class D, class H, class E>
void HashMap<K,D,H,E>::clear_freelist()
{
	while (_spill_freelist != END_OF_FREELIST) {
		unsigned i = _spill_freelist & 0x7fffffff;
		_spill_freelist = _data[i].marker;
		_data[i].marker = UNUSED;
	}
}

template<class K, class D, class H, class E>
template <class STREAM> void HashMap<K,D,H,E>::serialize(STREAM &stream)
{
	unsigned n = size();
	stream & n;
	if (stream.is_output()) {
		iterator it(this->begin());
		iterator end(this->end());
		for (; it != end; ++it)
			stream & (*it);
	} else {
		reserve(n);
		for (unsigned i=0; i<n; ++i) {
			value_type v(_data.allocator());
			stream & v;
			insert(v.first, v.second);
		}
	}

}


} // namespace stingray_plugin_foundation
