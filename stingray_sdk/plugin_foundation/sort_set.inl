namespace stingray_plugin_foundation {

template<class K, class C>
SortSet<K,C>::SortSet(Allocator &a) : _data(a)
{}

template<class K, class C>
SortSet<K,C>::SortSet(const SortSet<K, C> &o) : _less(o._less), _data(o._data)
{}

template<class K, class C>
void SortSet<K,C>::operator=(const SortSet<K,C> &o)
{
	_less = o._less;
	_data = o._data;
}

template<class K, class C>
void SortSet<K,C>::swap(SortSet<K,C> &o)
{
	std::swap(_less, o._less);
	std::swap(_data, o._data);
}

template <class K, class C>
template <class STREAM> void SortSet<K,C>::serialize(STREAM &stream)
{
	stream & _data;
}

template<class K, class C>
Allocator & SortSet<K,C>::allocator() const
{
	return _data.allocator();
}

template<class K, class C>
unsigned SortSet<K,C>::size() const
{
	return _data.size();
}

template<class K, class C>
void SortSet<K,C>::resize(unsigned size)
{
	_data.resize(size);
}

template<class K, class C>
bool SortSet<K,C>::empty() const
{
	return _data.empty();
}

template<class K, class C>
typename SortSet<K,C>::iterator SortSet<K,C>::begin()
{
	return _data.begin();
}

template<class K, class C>
typename SortSet<K,C>::const_iterator SortSet<K,C>::begin() const
{
	return _data.begin();
}

template<class K, class C>
typename SortSet<K,C>::iterator SortSet<K,C>::end()
{
	return _data.end();
}

template<class K, class C>
typename SortSet<K,C>::const_iterator SortSet<K,C>::end() const
{
	return _data.end();
}

template<class K, class C> template <class KEY_EQ>
unsigned SortSet<K,C>::find_index(const KEY_EQ &k) const
{
	unsigned lo = 0;
	unsigned hi = size();
	while (true) {
		if (hi <= lo)
			return size();
		unsigned mid = (lo + hi) / 2;
		if (_less(_data[mid], k))
			lo = mid+1;
		else if (_less(k, _data[mid]))
			hi = mid;
		else
			return mid;
	}
}

template<class K, class C> template <class KEY_EQ>
unsigned SortSet<K,C>::lower_bound_index(const KEY_EQ &k) const
{
	unsigned lo = 0;
	unsigned hi = size();

	if (hi == 0 || !_less(_data[lo], k))
		return 0;

	while (true) {
		if (hi <= lo+1)
			return hi;
		unsigned mid = (lo + hi) / 2;
		if (_less(_data[mid], k))
			lo = mid;
		else
			hi = mid;
	}
}

template<class K, class C> template <class KEY_EQ>
unsigned SortSet<K,C>::upper_bound_index(const KEY_EQ &k) const
{
	unsigned lo = 0;
	unsigned hi = size();

	if (hi == 0 || _less(k, _data[lo]))
		return 0;

	while (true) {
		if (hi <= lo+1)
			return hi;
		unsigned mid = (lo + hi) / 2;
		if (_less(k, _data[mid]))
			hi = mid;
		else
			lo = mid;
	}
}

template<class K, class C> template <class KEY_EQ>
typename SortSet<K,C>::iterator SortSet<K,C>::find(const KEY_EQ &k)
{
	return begin() + find_index(k);
}

template<class K, class C> template <class KEY_EQ>
typename SortSet<K,C>::const_iterator SortSet<K,C>::find(const KEY_EQ &k) const
{
	return begin() + find_index(k);
}

template<class K, class C> template <class KEY_EQ>
typename SortSet<K,C>::iterator SortSet<K,C>::lower_bound(const KEY_EQ &k)
{
	return begin() + lower_bound_index(k);
}

template<class K, class C> template <class KEY_EQ>
typename SortSet<K,C>::const_iterator SortSet<K,C>::lower_bound(const KEY_EQ &k) const
{
	return begin() + lower_bound_index(k);
}

template<class K, class C> template <class KEY_EQ>
typename SortSet<K,C>::iterator SortSet<K,C>::upper_bound(const KEY_EQ &k)
{
	return begin() + upper_bound_index(k);
}

template<class K, class C> template <class KEY_EQ>
typename SortSet<K,C>::const_iterator SortSet<K,C>::upper_bound(const KEY_EQ &k) const
{
	return begin() + upper_bound_index(k);
}

template<class K, class C> template <class KEY_EQ>
bool SortSet<K,C>::has(const KEY_EQ &k) const
{
	return find(k) != end();
}

template<class K, class C> template <class KEY_EQ>
int SortSet<K,C>::count(const KEY_EQ &k) const
{
	return upper_bound_index(k) - lower_bound_index(k);
}

template<class K, class C>
void SortSet<K,C>::clear()
{
	_data.clear();
}

template<class K, class C> template <class KEY_EQ>
void SortSet<K,C>::insert(const KEY_EQ &k)
{
	_data.resize( _data.size()+1 );
	_data.back() = k;
}

template<class K, class C>
typename SortSet<K,C>::iterator SortSet<K,C>::erase(iterator i)
{
	return _data.erase(i);
}

template<class K, class C> template <class KEY_EQ>
void SortSet<K,C>::erase(const KEY_EQ &k)
{
	_data.erase( find(k) );
}

template<class K, class C>
void SortSet<K,C>::sort()
{
	std::sort(_data.begin(), _data.end(), _less);
}

template<class K, class C>
void SortSet<K,C>::trim()
{
	_data.trim();
}

template <class K, class C>
bool SortSet<K,C>::is_multi_set() const
{
	for (unsigned i=1; i<_data.size(); ++i) {
		if (!_less(_data[i], _data[i-1]) &&
			!_less(_data[i-1], _data[i]))
			return true;
	}
	return false;
}

} // namespace stingray_plugin_foundation
