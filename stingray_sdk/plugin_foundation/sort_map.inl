#include "assert.h"

namespace stingray_plugin_foundation {

template <class K, class D, class C>
SortMap<K,D,C>::SortMap(Allocator &a) : _data(a)
{
	mark_sorted();
}

template <class K, class D, class C>
SortMap<K,D,C>::SortMap(const NoAllocator &a) : _data(a)
{
	mark_sorted();
}

template <class K, class D, class C>
void SortMap<K,D,C>::set_capacity(unsigned capacity)
{
	_data.set_capacity(capacity);
}

template <class K, class D, class C>
void SortMap<K,D,C>::set_allocator(Allocator &allocator)
{
	_data.set_allocator(allocator);
}

template <class K, class D, class C>
SortMap<K,D,C>::SortMap(const SortMap<K,D,C> &o) : _less(o._less), _data(o._data)
{
	#ifdef DEVELOPMENT
		_is_sorted = o._is_sorted;
	#endif
}

template <class K, class D, class C>
void SortMap<K,D,C>::operator=(const SortMap<K,D,C> &o)
{
	_less = o._less;
	_data = o._data;
	#ifdef DEVELOPMENT
		_is_sorted = o._is_sorted;
	#endif
}

template <class K, class D, class C>
void SortMap<K,D,C>::swap(SortMap<K,D,C> &o)
{
	std::swap(_less, o._less);
	std::swap(_data, o._data);
	#ifdef DEVELOPMENT
		std::swap(_is_sorted, o._is_sorted);
	#endif
}

template <class K, class D, class C>
Allocator &SortMap<K,D,C>::allocator() const
{
	return _data.allocator();
}

template <class K, class D, class C>
unsigned SortMap<K,D,C>::size() const
{
	return _data.size();
}

template <class K, class D, class C>
bool SortMap<K,D,C>::empty() const
{
	return _data.empty();
}

template <class K, class D, class C>
typename SortMap<K,D,C>::iterator SortMap<K,D,C>::begin()
{
	return _data.begin();
}

template <class K, class D, class C>
typename SortMap<K,D,C>::const_iterator SortMap<K,D,C>::begin() const
{
	return _data.begin();
}

template <class K, class D, class C>
typename SortMap<K,D,C>::iterator SortMap<K,D,C>::end()
{
	return _data.end();
}

template <class K, class D, class C>
typename SortMap<K,D,C>::const_iterator SortMap<K,D,C>::end() const
{
	return _data.end();
}

template <class K, class D, class C> template <class KEY_EQ>
typename SortMap<K,D,C>::iterator SortMap<K,D,C>::find(const KEY_EQ &k)
{
	check_sorted();
	return begin() + find_index(k);
}

template <class K, class D, class C> template <class KEY_EQ>
typename SortMap<K,D,C>::const_iterator SortMap<K,D,C>::find(const KEY_EQ &k) const
{
	check_sorted();
	return begin() + find_index(k);
}

template <class K, class D, class C> template <class KEY_EQ>
typename SortMap<K,D,C>::iterator SortMap<K,D,C>::lower_bound(const KEY_EQ &k)
{
	check_sorted();
	return begin() + lower_bound_index(k);
}

template <class K, class D, class C> template <class KEY_EQ>
const typename SortMap<K,D,C>::iterator SortMap<K,D,C>::lower_bound(const KEY_EQ &k) const
{
	check_sorted();
	return begin() + lower_bound_index(k);
}

template <class K, class D, class C> template <class KEY_EQ>
typename SortMap<K,D,C>::iterator SortMap<K,D,C>::upper_bound(const KEY_EQ &k)
{
	check_sorted();
	return begin() + upper_bound_index(k);
}

template <class K, class D, class C> template <class KEY_EQ>
const typename SortMap<K,D,C>::iterator SortMap<K,D,C>::upper_bound(const KEY_EQ &k) const
{
	check_sorted();
	return begin() + upper_bound_index(k);
}

template <class K, class D, class C> template <class KEY_EQ>
bool SortMap<K,D,C>::has(const KEY_EQ &k) const
{
	return find(k) != end();
}

template <class K, class D, class C> template <class KEY_EQ>
int SortMap<K,D,C>::count(const KEY_EQ &k) const
{
	return upper_bound_index(k) - lower_bound_index(k);
}

template <class K, class D, class C>
typename SortMap<K,D,C>::key_type &SortMap<K,D,C>::key(int i)
{
	return _data[i].first;
}

template <class K, class D, class C>
const typename SortMap<K,D,C>::key_type &SortMap<K,D,C>::key(int i) const
{
	return _data[i].first;
}

template <class K, class D, class C>
typename SortMap<K,D,C>::data_type &SortMap<K,D,C>::data(int i)
{
	return _data[i].second;
}

template <class K, class D, class C>
const typename SortMap<K,D,C>::data_type & SortMap<K,D,C>::data(int i) const
{
	return _data[i].second;
}

template <class K, class D, class C>
typename SortMap<K,D,C>::value_type &SortMap<K,D,C>::value(int i)
{
	return _data[i];
}

template <class K, class D, class C>
const typename SortMap<K,D,C>::value_type & SortMap<K,D,C>::value(int i) const
{
	return _data[i];
}

template <class K, class D, class C>
typename SortMap<K,D,C>::value_type &SortMap<K,D,C>::front()
{
	return _data.front();
}

template <class K, class D, class C>
const typename SortMap<K,D,C>::value_type & SortMap<K,D,C>::front() const
{
	return _data.front();
}

template <class K, class D, class C>
typename SortMap<K,D,C>::value_type &SortMap<K,D,C>::back()
{
	return _data.back();
}

template <class K, class D, class C>
const typename SortMap<K,D,C>::value_type & SortMap<K,D,C>::back() const
{
	return _data.back();
}

template <class K, class D, class C> template <class KEY_EQ>
const typename SortMap<K,D,C>::data_type & SortMap<K,D,C>::operator[](const KEY_EQ &k) const
{
	return find(k)->second;
}

template <class K, class D, class C> template <class KEY_EQ>
typename SortMap<K,D,C>::data_type & SortMap<K,D,C>::operator[](const KEY_EQ &k)
{
	iterator it = find(k);
	XENSURE(it != end());
	return it->second;
}

template <class K, class D, class C> template <class KEY_EQ>
const typename SortMap<K,D,C>::data_type & SortMap<K,D,C>::get(const KEY_EQ &k, const data_type &def) const
{
	const_iterator it = find(k);
	if (it == end()) return def;
	return it->second;
}

template <class K, class D, class C>
void SortMap<K,D,C>::clear()
{
	_data.clear();
	mark_sorted();
}

template <class K, class D, class C> template <class KEY_EQ, class DATA_EQ>
void SortMap<K,D,C>::insert(const KEY_EQ &k, const DATA_EQ &v)
{
	// It might be better to inplace construct the pair in the
	// vector rather than constructing and copying... I'm not sure
	// if that can be done.
	_data.resize( _data.size() +  1);
	_data.back().first = k;
	#pragma warning(push)
	#pragma warning(disable : 4267) // templated, hard to fix warning for possible data loss
	_data.back().second = v;
	#pragma warning(pop)
	mark_unsorted();
}

template <class K, class D, class C> template <class KEY_EQ>
void SortMap<K,D,C>::insert(iterator pos, const KEY_EQ &k, const data_type &v)
{
	value_type value(k,v);
	_data.insert(pos, value);
	mark_unsorted();
}

template <class K, class D, class C>
typename SortMap<K,D,C>::iterator SortMap<K,D,C>::erase(iterator i)
{
	return _data.erase(i);
}

template <class K, class D, class C> template <class KEY_EQ>
void SortMap<K,D,C>::erase(const KEY_EQ &k)
{
	_data.erase( find(k) );
}

template <class K, class D, class C>
void SortMap<K,D,C>::sort()
{
	std::sort(_data.begin(), _data.end(), value_compare(_less));
	mark_sorted();
}


template <class K, class D, class C>
bool SortMap<K,D,C>::is_multi_map()
{
	check_sorted();
	for (unsigned i=1; i<_data.size(); ++i) {
		if (!_less(_data[i].first, _data[i-1].first) &&
			!_less(_data[i-1].first, _data[i].first))
			return true;
	}
	return false;
}

template <class K, class D, class C>
void SortMap<K,D,C>::trim()
{
	_data.trim();
}

template <class K, class D, class C>
void SortMap<K,D,C>::reserve(unsigned n)
{
	_data.reserve(n);
}

template <class K, class D, class C>
void SortMap<K,D,C>::resize(unsigned n)
{
	_data.resize(n);
}

template <class K, class D, class C> template <class KEY_EQ>
unsigned SortMap<K,D,C>::find_index(const KEY_EQ &k) const
{
	unsigned lo = 0;
	unsigned hi = size();
	while (true) {
		if (hi <= lo)
			return size();
		unsigned mid = (lo + hi) / 2;
		if (_less(_data[mid].first, k))
			lo = mid+1;
		else if (_less(k, _data[mid].first))
			hi = mid;
		else
			return mid;
	}
}

template <class K, class D, class C> template <class KEY_EQ>
unsigned SortMap<K,D,C>::lower_bound_index(const KEY_EQ &k) const
{
	unsigned lo = 0;
	unsigned hi = size();

	if (hi == 0 || !_less(_data[lo].first, k))
		return 0;

	while (true) {
		if (hi <= lo+1)
			return hi;
		unsigned mid = (lo + hi) / 2;
		if (_less(_data[mid].first, k))
			lo = mid;
		else
			hi = mid;
	}
}

template <class K, class D, class C> template <class KEY_EQ>
unsigned SortMap<K,D,C>::upper_bound_index(const KEY_EQ &k) const
{
	unsigned lo = 0;
	unsigned hi = size();

	if (hi == 0 || _less(k, _data[lo].first))
		return 0;

	while (true) {
		if (hi <= lo+1)
			return hi;
		unsigned mid = (lo + hi) / 2;
		if (_less(k, _data[mid].first))
			hi = mid;
		else
			lo = mid;
	}
}

template <class K, class D, class C>
void SortMap<K,D,C>::mark_sorted()
{
	#ifdef DEVELOPMENT
		_is_sorted = true;
	#endif
}

template <class K, class D, class C>
void SortMap<K,D,C>::mark_unsorted()
{
	#ifdef DEVELOPMENT
		_is_sorted = false;
	#endif
}

template <class K, class D, class C>
void SortMap<K,D,C>::check_sorted() const
{
	XASSERT(_is_sorted, "SortMap not sorted");
}

template<class K, class D, class C>
template <class STREAM> void SortMap<K,D,C>::serialize(STREAM &stream)
{
	check_sorted();
	stream & _data;
	mark_sorted();
}

} // namespace stingray_plugin_foundation
