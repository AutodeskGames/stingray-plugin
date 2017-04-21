#pragma once

#include "pair.h"
#include "vector.h"

#include "allocator.h"

#include "functional.h"

namespace stingray_plugin_foundation {

// A map data structure that needs to be explicitly sorted.
//
// This map is just a thin wrapper around a sorted Vector and has
// the expected performance characteristics. Since data is stored
// linearly it is very cache friendly and it should be fast for most
// operations unless the map is huge, in which case an UnsortedMap
// is better.
//
// Note that the map must be explicitly sorted before any lookups
// can be performed and inserting new objects requires a resort.
// If frequent insertion is needed, use an UnsortedMap or a Map instead.
//
// Warning: Any operation requiring data lookup, such as
//		[], erase, begin, end, find, etc, won't work as expected unless
//		the map has been sorted. Remember to call sort before doing such
//		operations.
//
// * `K`			The key type of the map.
// * `D`			The data type of the map.
// * `COMPARE`		The less-than compare functor, defaults to std::less<K>.
template <class K, class D, class COMPARE = less >
class SortMap
{
public:
	ALLOCATOR_AWARE;

	typedef K key_type;
	typedef D data_type;
	typedef COMPARE key_compare;
	typedef Pair<key_type, data_type, IS_ALLOCATOR_AWARE(key_type), IS_ALLOCATOR_AWARE(data_type)> value_type;
	typedef Vector<value_type> storage_type;
	typedef typename storage_type::iterator iterator;
	typedef typename storage_type::const_iterator const_iterator;

	SortMap(const NoAllocator &a);
	explicit SortMap(Allocator &a);
	SortMap(const SortMap<K,D,COMPARE> &o);
	void operator=(const SortMap<K,D,COMPARE> &o);
	void swap(SortMap<K,D,COMPARE> &o);

	Allocator &allocator() const;

	// Sets the allocator of the sort map. You can only call this before any
	// allocations have been made by the vector.
	void set_allocator(Allocator &allocator);

	// Serializes the map to the stream.
	template <class STREAM> void serialize(STREAM &stream);

	unsigned size() const;
	bool empty() const;
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	template <class KEY_EQ> iterator find(const KEY_EQ &k);
	template <class KEY_EQ> const_iterator find(const KEY_EQ &k) const;
	template <class KEY_EQ> iterator lower_bound(const KEY_EQ &k);
	template <class KEY_EQ> const iterator lower_bound(const KEY_EQ &k) const;
	template <class KEY_EQ> iterator upper_bound(const KEY_EQ &k);
	template <class KEY_EQ> const iterator upper_bound(const KEY_EQ &k) const;
	template <class KEY_EQ> unsigned lower_bound_index(const KEY_EQ &k) const;
	template <class KEY_EQ> unsigned upper_bound_index(const KEY_EQ &k) const;

	// True if the map has the key `k`.
	template <class KEY_EQ> bool has(const KEY_EQ &k) const;

	// Number of occurances of the key `k`.
	template <class KEY_EQ> int count(const KEY_EQ &k) const;

	// Access keys by index.
	key_type &key(int i);
	// Access keys by index.
	const key_type &key(int i) const;
	// Access data by index.
	data_type &data(int i);
	// Access data by index.
	const data_type &data(int i) const;
	// Access value by index.
	value_type &value(int i);
	// Access data by index.
	const value_type &value(int i) const;

	value_type &front();
	const value_type &front() const;

	value_type &back();
	const value_type &back() const;

	// Returns the value for the key `k`. The behavior is undefined if the key
	// does not exist.
	template <class KEY_EQ> const data_type &operator[](const KEY_EQ &k) const;

	// Unlike std::map, [] cannot be used to insert new keys in a SortMap,
	// only to change the values of existing keys. Returns a reference to
	// the value. The behavior is undefined if the map doesn't have the key `k`.
	template <class KEY_EQ> data_type &operator[](const KEY_EQ &k);

	// Returns the value for the key `k` or `def` if the key doesn't exist.
	template <class KEY_EQ> const data_type &get(const KEY_EQ &k, const data_type &def) const;

	// Clears all elements in the sort map (but does not deallocate memory).
	void clear();

	// Resets the sort map to its initial state (no memory allocated).
	void reset() {set_capacity(0);}

	// Sets the capacity of the sort map to exactly the specified number of elements.
	// This operation always reallocates the memory of the backing vector, no
	// swap trick is necessary to enforce reallocation.
	void set_capacity(unsigned capacity);

	// Inserts the data pair (`k`, `v`) at the end of the map.
	template <class KEY_EQ, class DATA_EQ> void insert(const KEY_EQ &k, const DATA_EQ &v);

	// Inserts the data pair (`k`, `v`) at the iterator position.
	template <class KEY_EQ> void insert(iterator pos, const KEY_EQ &k, const data_type &v);

	iterator erase(iterator i);
	template <class KEY_EQ> void erase(const KEY_EQ &k);

	#ifdef DEVELOPMENT
		// Returns true if the map is sorted.
		bool is_sorted();
	#endif

	// Sorts the map. You must call this before using any function that looks up
	// values by key.
	void sort();

	// Marks the map as sorted (without sorting it). Use this if you know that
	// the elements have been inserted in sorted order.
	void mark_sorted();

	// Returns true if the map contains duplicate keys.
	// You must sort the map before using this function.
	bool is_multi_map();

	// Sets the capacity of this map to its current size.
	void trim();

	// Reserves space
	void reserve(unsigned n);

	// Resizes
	void resize(unsigned n);

private:
	template <class KEY_EQ> unsigned find_index(const KEY_EQ &k) const;
	void mark_unsorted();
	void check_sorted() const;

	class value_compare {
	public:
		value_compare(key_compare less) : _less(less) {}
		bool operator()(const value_type& left, const value_type& right) const
			{return (_less(left.first, right.first));}
	protected:
		key_compare _less;
	};

	key_compare _less;
	storage_type _data;

	#ifdef DEVELOPMENT
		bool _is_sorted;
	#endif
};

} // namespace stingray_plugin_foundation

#include "sort_map.inl"
