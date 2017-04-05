#pragma once

#include "vector.h"
#include "hash_function.h"
#include "bucket_iterator.h"
#include "allocator.h"
#include "template_tools.h"
#include "functional.h"

namespace stingray_plugin_foundation {

// Implementation of set using the same technique as HashMap.
// @see HashMap
template <class K, class HASH = default_hash<K>, class EQUAL = equal_to >
class HashSet
{
public:
	ALLOCATOR_AWARE;

	typedef K key_type;
	typedef HASH key_hash;
	typedef EQUAL key_equal;
	typedef HashSet<K, HASH, EQUAL> this_type;

	template <class T, int N>
	struct node_type_base {
		key_type	value;
		unsigned	marker;
	};

	template <int N>
	struct node_type_base< Int2Type<true>, N > {
		ALLOCATOR_AWARE;
		node_type_base(Allocator &a) : value(a) {}
		key_type	value;
		unsigned	marker;
	};
	typedef node_type_base< IS_ALLOCATOR_AWARE_TYPE(K), 0 > node_type;
	typedef Vector< node_type> storage_type;
	typedef ConstBucketIterator<this_type, key_type> const_iterator;
	typedef BucketIterator<this_type, key_type> iterator;

	enum {END_OF_LIST = 0x7fffffff, UNUSED = 0xfffffffe, END_OF_FREELIST = 0xffffffff};

	HashSet(Allocator &a);
	HashSet(unsigned buckets, unsigned spill, Allocator &a);
	HashSet(const HashSet<K,HASH,EQUAL> &o);
	void operator=(const HashSet<K,HASH,EQUAL> &o);

	void reserve(unsigned size);

	void swap(HashSet<K,HASH,EQUAL> &o);
	Allocator & allocator() const;
	unsigned size() const;
	bool empty() const;

	template <class KEY_EQ> bool has(const KEY_EQ &k) const;
	void clear();
	template <class KEY_EQ> void insert(const KEY_EQ &k);
	template <class KEY_EQ> void erase(const KEY_EQ &k);
	void rehash(unsigned new_buckets);

	const_iterator begin() const;
	const_iterator end() const;

	unsigned num_buckets() const;
	bool bucket_valid(unsigned i) const;
	const key_type &bucket_value(unsigned i) const;
	key_type &bucket_value(unsigned i);

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

	key_hash		_hash;
	key_equal		_equal;
	storage_type	_data;
	unsigned		_used;
	unsigned		_buckets;
	unsigned		_spill_unused;
	unsigned		_spill_freelist;
};

} // namespace stingray_plugin_foundation

#include "hash_set.inl"
