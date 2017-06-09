#pragma once

#include "hash_function.h"
#include "pair.h"
#include "bucket_iterator.h"
#include "vector.h"
#include "functional.h"

namespace stingray_plugin_foundation {

// Implements an unordered map using a hash table.
//
// The hash table allocates its memory in a single block to be as cache
// friendly as possible. Hash collisions are resolved by chaining into
// a separate region of that memory block. This avoids clustering while
// also avoiding the cache inefficiency of linked lists.
//
// A lookup in the spillover area will likely lead to a cache miss, so
// from a cache perspective linear probing might be more efficient.
// OTOH linear probing has a tendency to cause clustering which can
// heavily degrade performance. It also complicates hash table deletes.
//
// For a randomly distributed hash function, a lookup in this hash table
// on average has too look at 1.3 nodes. The expected memory use is
//
// $ 1.37 n (K_s D_s + 4) $,
//
// where `n` is the number of elements and `K_s` is the size of
// the key elements and `D_s` is the size of the data elements. The
// spillover region is set to 37 % of the hash region size. Experimentally
// this has been found to be a good trade off value.
//
// HashMap is a good choice when you need to insert and lookup continuously
// (so you can't use SortMap) and you don't need to do an ordered traversal
// of the items.
// \tparam K the key type
// \tparam D the data type
// \tparam HASH  hash functor, defaults to default_hash>
// \tparam EQUAL equality functor, defaults to std::equal_to<K>
template <class K, class D, class HASH = default_hash<K>, class EQUAL = equal_to >
class HashMap
{
public:
	ALLOCATOR_AWARE;

	typedef K key_type;
	typedef D data_type;
	typedef HASH key_hash;
	typedef EQUAL key_equal;
	typedef HashMap<K, D, HASH, EQUAL> this_type;
	typedef Pair<key_type, data_type, IS_ALLOCATOR_AWARE(key_type), IS_ALLOCATOR_AWARE(data_type)> value_type;

	// Special values for marker
	enum {END_OF_LIST = 0x7fffffff, UNUSED = 0xfffffffe, END_OF_FREELIST = 0xffffffff};

	typedef BucketIterator<this_type, value_type> iterator;
	typedef ConstBucketIterator<this_type, value_type> const_iterator;

	HashMap(Allocator &a);
	// Creates an unordered map presized to the specified number of buckets and
	// spill-over buckets. It is recommended that spill = 0.37 * buckets.
	HashMap(unsigned buckets, unsigned spill, Allocator &a);
	HashMap(const HashMap<K,D,HASH,EQUAL> &o);
	~HashMap();

	void operator=(const HashMap<K,D,HASH,EQUAL> &o);
	void swap(HashMap<K,D,HASH,EQUAL> &o);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	template <class KEY_EQ> const_iterator find(const KEY_EQ &k) const;
	template <class KEY_EQ> iterator find(const KEY_EQ &k);

	Allocator & allocator() const;

	void reserve(unsigned size);
	unsigned size() const;
	bool empty() const;

	// Returns true if the key is in the hash
	template <class KEY_EQ> bool has(const KEY_EQ &k) const;
	template <class KEY_EQ> data_type &operator[](const KEY_EQ &k);
	template <class KEY_EQ> value_type &get_pair(const KEY_EQ &k);
	template <class KEY_EQ> const data_type &operator[](const KEY_EQ &k) const;
	// Returns the value for `k` if it exists and `def` otherwise.
	template <class KEY_EQ> data_type &get(const KEY_EQ &k, data_type &def);
	template <class KEY_EQ> const data_type &get(const KEY_EQ &k, const data_type &def) const;
	void clear();
	// Inserts the data point (`k`, `v`) in the map.
	template <class KEY_EQ, class DATA_EQ> void insert(const KEY_EQ &k, const DATA_EQ &v);
	template <class KEY_EQ> void erase(const KEY_EQ &k);

	// Rehashes the data to the specified number of buckets (and a spill
	// region of 0.37 * buckets).
	// You can use this to reserve memory in the hash before inserting a lot
	// of elements to avoid rehashing during insertion. You can also use it
	// to shrink a hash, but you cannot shrink a hash beyond its current size.
	void rehash(unsigned new_buckets);

	// Used by iterator
	unsigned num_buckets() const;
	bool bucket_valid(unsigned i) const;
	value_type &bucket_value(unsigned i);
	const value_type &bucket_value(unsigned i) const;

	// Serializes the hash map to the stream.
	template <class STREAM> void serialize(STREAM &stream);

private:
	template <class KEY_EQ> unsigned find_or_fail(const KEY_EQ &k) const;
	template <class KEY_EQ> unsigned find_or_make(const KEY_EQ &k);
	template <class KEY_EQ> void find_and_erase(const KEY_EQ &k);
	bool full() const;
	void grow();
	template <class KEY_EQ> unsigned hash(const KEY_EQ &k) const;
	unsigned allocate_spill();
	void free_spill(unsigned i);
	void clear_freelist();
	void allocate_data(unsigned count);
	void construct(value_type &p) { new (&p) value_type(_allocator); }
	void destruct(value_type &p) { p.~value_type(); }

	struct Data {
		Data() : size(), marker(), value() {}
		unsigned size;
		unsigned *marker;
		value_type *value;
	};

	key_hash		_hash;
	key_equal		_equal;
	Data			_data;
	unsigned		_used;
	unsigned		_buckets;
	unsigned		_spill_unused;
	unsigned		_spill_freelist;
	Allocator		&_allocator;
};

} // namespace stingray_plugin_foundation

#include "hash_map.inl"
