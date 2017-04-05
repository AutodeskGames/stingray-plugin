#pragma once

#include "functional.h"

namespace stingray_plugin_foundation {

// Set implementation having the same structure and performance characteristics as
// SortedMap.
template < class K, class COMPARE = less >
class SortSet
{
public:
	ALLOCATOR_AWARE;

	typedef K key_type;
	typedef COMPARE key_compare;
	typedef Vector<key_type> storage_type;
	typedef typename storage_type::iterator iterator;
	typedef typename storage_type::const_iterator const_iterator;

	explicit SortSet(Allocator &a);
	explicit SortSet(const SortSet<K,COMPARE> &o);
	void operator=(const SortSet<K,COMPARE> &o);
	void swap(SortSet<K,COMPARE> &o);

	// Serializes the sort set to the stream.
	template <class STREAM>	void serialize(STREAM &stream);

	Allocator & allocator() const;

	unsigned size() const;
	void resize(unsigned size);
	bool empty() const;
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	template <class KEY_EQ> unsigned find_index(const KEY_EQ &k) const;
	template <class KEY_EQ> unsigned lower_bound_index(const KEY_EQ &k) const;
	template <class KEY_EQ> unsigned upper_bound_index(const KEY_EQ &k) const;

	template <class KEY_EQ> iterator find(const KEY_EQ &k);
	template <class KEY_EQ> const_iterator find(const KEY_EQ &k) const;
	template <class KEY_EQ> iterator lower_bound(const KEY_EQ &k);
	template <class KEY_EQ> const_iterator lower_bound(const KEY_EQ &k) const;
	template <class KEY_EQ> iterator upper_bound(const KEY_EQ &k);
	template <class KEY_EQ> const_iterator upper_bound(const KEY_EQ &k) const;

	template <class KEY_EQ> bool has(const KEY_EQ &k) const;
	template <class KEY_EQ> int count(const KEY_EQ &k) const;

	void clear();
	template <class KEY_EQ> void insert(const KEY_EQ &k);
	iterator erase(iterator i);
	template <class KEY_EQ> void erase(const KEY_EQ &k);
	void sort();
	void trim();
	bool is_multi_set() const;

private:
	key_compare _less;
	storage_type _data;
};

} // namespace stingray_plugin_foundation

#include "sort_set.inl"
