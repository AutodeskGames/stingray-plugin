#pragma once

namespace stingray_plugin_foundation {

template <class CONTAINER, class ITEM>
class ConstBucketIterator;

// A helper class that makes an iterator for a bucket based data structure.
// Such a data structure has a number of random access buckets which may be
// "valid" or not. The iterator iterates over the valid buckets only.
template <class CONTAINER, class ITEM>
class BucketIterator {
public:
	typedef BucketIterator<CONTAINER, ITEM> iterator;
	friend class ConstBucketIterator<CONTAINER, ITEM>;

	typedef ITEM value_type;
	typedef ITEM* pointer;
	typedef ITEM& reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	inline BucketIterator() : _i(0) { }
	inline BucketIterator(CONTAINER &container, unsigned i);
	inline BucketIterator(const BucketIterator &other);

	inline bool operator==(const iterator &rhs) const	{ return cmp(rhs) == 0; }
	inline bool operator!=(const iterator &rhs) const	{ return cmp(rhs) != 0; }
	inline bool operator<(const iterator &rhs) const	{ return cmp(rhs) <  0; }
	inline bool operator<=(const iterator &rhs) const	{ return cmp(rhs) <=  0; }
	inline bool operator>(const iterator &rhs) const	{ return cmp(rhs) >  0; }
	inline bool operator>=(const iterator &rhs) const	{ return cmp(rhs) >=  0; }

	inline iterator operator++();
	inline iterator operator++(int);

	inline ITEM &operator*()				{ return _container->bucket_value(_i); }
	inline ITEM *operator->()				{ return &_container->bucket_value(_i); }

private:
	inline int cmp(const iterator &rhs) const {
		if(_container < rhs._container) return -1;
		else if(_container > rhs._container) return 1;
		else if(_i < rhs._i) return -1;
		else if(_i > rhs._i) return 1;
		else return 0;
	}

	void advance_to_valid_bucket();

	CONTAINER *_container;
	unsigned _i;
};

// A helper class that makes an iterator for a bucket based data structure.
// Such a data structure has a number of random access buckets which may be
// "valid" or not. The iterator iterates over the valid buckets only.
template <class CONTAINER, class ITEM>
class ConstBucketIterator {
public:
	typedef ConstBucketIterator<CONTAINER, ITEM> iterator;

	typedef ITEM value_type;
	typedef ITEM* pointer;
	typedef ITEM& reference;
	typedef ptrdiff_t difference_type;
	typedef std::forward_iterator_tag iterator_category;

	inline ConstBucketIterator() : _i(0) {}
	inline ConstBucketIterator(const CONTAINER &container, unsigned i);
	inline ConstBucketIterator(const ConstBucketIterator<CONTAINER, ITEM> &rhs);
	inline ConstBucketIterator(const BucketIterator<CONTAINER, ITEM> &rhs);

	inline bool operator==(const iterator &rhs) const	{ return cmp(rhs) == 0; }
	inline bool operator!=(const iterator &rhs) const	{ return cmp(rhs) != 0; }
	inline bool operator<(const iterator &rhs) const	{ return cmp(rhs) <  0; }
	inline bool operator<=(const iterator &rhs) const	{ return cmp(rhs) <=  0; }
	inline bool operator>(const iterator &rhs) const	{ return cmp(rhs) >  0; }
	inline bool operator>=(const iterator &rhs) const	{ return cmp(rhs) >=  0; }

	inline iterator operator++();
	inline iterator operator++(int);

	inline const ITEM &operator*()				{ return _container->bucket_value(_i); }
	inline const ITEM *operator->()				{ return &_container->bucket_value(_i); }

private:
	inline int cmp(const iterator &rhs) const {if (_container != rhs._container) return (int)(_container - rhs._container); return (int)(_i - rhs._i);}
	void advance_to_valid_bucket();

	const CONTAINER *_container;
	unsigned _i;
};

} // namespace stingray_plugin_foundation

#include "bucket_iterator.inl"
