#pragma once

#include <algorithm>
#include "allocator.h"
#include "template_tools.h"

namespace stingray_plugin_foundation {

// A replacement for std::pair that is allocator aware, so that any
// of the pair members that need to be constructed with an allocator is.
//
// The default template implementation is used when none of the types
// are allocator aware.
template <class FIRST, class SECOND, bool firstaware, bool secondaware>
struct Pair {
	typedef Pair<FIRST, SECOND, firstaware, secondaware> this_type;
	typedef FIRST first_type;
	typedef SECOND second_type;

	Pair() : first(first_type()), second(second_type()) {}
	Pair(Allocator &) : first(first_type()), second(second_type()) {}
	Pair(const this_type &t) : first(t.first), second(t.second) {}
	Pair(const first_type &f, const second_type &s) : first(f), second(s) {}

	void swap(this_type &right) {
		std::swap(first, right.first);
		std::swap(second, right.second);
	}

	template <class STREAM> void serialize(STREAM &s) {s & first & second;}

	first_type first;
	second_type second;
};

// Template specialization to use when the first type is allocator aware.
template <class FIRST, class SECOND>
struct Pair<FIRST, SECOND, true, false>
{
	ALLOCATOR_AWARE;

	typedef Pair<FIRST, SECOND, true, false> this_type;
	typedef FIRST first_type;
	typedef SECOND second_type;

	Pair(Allocator &a) : first(a), second(second_type()) {}
	Pair(const first_type &f, const second_type &s) : first(f), second(s) {}

	void swap(this_type &right) {
		std::swap(first, right.first);
		std::swap(second, right.second);
	}

	template <class STREAM> void serialize(STREAM &s) {s & first & second;}

	first_type first;
	second_type second;
};

// Template specialization to use when the second type is allocator aware.
template <class FIRST, class SECOND>
struct Pair<FIRST, SECOND, false, true>
{
	ALLOCATOR_AWARE;

	typedef Pair<FIRST, SECOND, false, true> this_type;
	typedef FIRST first_type;
	typedef SECOND second_type;

	Pair(Allocator &a) : first(first_type()), second(a) {}
	Pair(const first_type &f, const second_type &s) : first(f), second(s) {}

	void swap(this_type &right) {
		std::swap(first, right.first);
		std::swap(second, right.second);
	}

	template <class STREAM> void serialize(STREAM &s) {s & first & second;}

	first_type first;
	second_type second;
};

// Template specialization to use when both types are allocator aware.
template <class FIRST, class SECOND>
struct Pair<FIRST, SECOND, true, true>
{
	ALLOCATOR_AWARE;

	typedef Pair<FIRST, SECOND, true, true> this_type;
	typedef FIRST first_type;
	typedef SECOND second_type;

	Pair(Allocator &a) : first(a), second(a) {}
	Pair(const first_type &f, const second_type &s) : first(f), second(s) {}

	void swap(this_type &right) {
		std::swap(first, right.first);
		std::swap(second, right.second);
	}

	template <class STREAM> void serialize(STREAM &s) {s & first & second;}

	first_type first;
	second_type second;
};

// Comparison operators.

template <class FIRST, class SECOND, bool firstaware, bool secondaware>
bool operator==(const Pair<FIRST,SECOND,firstaware,secondaware> &left,
				const Pair<FIRST,SECOND,firstaware,secondaware> &right) {
	return left.first == right.first && left.second == right.second;
}

template <class FIRST, class SECOND, bool firstaware, bool secondaware>
bool operator!=(const Pair<FIRST,SECOND,firstaware,secondaware> &left,
				const Pair<FIRST,SECOND,firstaware,secondaware> &right) {
	return !(left == right);
}

template <class FIRST, class SECOND, bool firstaware, bool secondaware>
bool operator<(const Pair<FIRST,SECOND,firstaware,secondaware> &left,
				const Pair<FIRST,SECOND,firstaware,secondaware> &right) {
	return left.first < right.first ||
			(!(right.first < left.first) && left.second < right.second);
}

template <class FIRST, class SECOND, bool firstaware, bool secondaware>
bool operator>(const Pair<FIRST,SECOND,firstaware,secondaware> &left,
			   const Pair<FIRST,SECOND,firstaware,secondaware> &right) {
	return (right < left);
}

template <class FIRST, class SECOND, bool firstaware, bool secondaware>
bool operator<=(const Pair<FIRST,SECOND,firstaware,secondaware> &left,
			   const Pair<FIRST,SECOND,firstaware,secondaware> &right) {
	return !(right < left);
}

template <class FIRST, class SECOND, bool firstaware, bool secondaware>
bool operator>=(const Pair<FIRST,SECOND,firstaware,secondaware> &left,
				const Pair<FIRST,SECOND,firstaware,secondaware> &right) {
	return !(left < right);
}

// make_pair function that constructs a Pair of the right type
template <class FIRST, class SECOND>
Pair<FIRST, SECOND, IS_ALLOCATOR_AWARE(FIRST), IS_ALLOCATOR_AWARE(SECOND)> make_pair(const FIRST &f, const SECOND &s)
{
	return Pair<FIRST, SECOND, IS_ALLOCATOR_AWARE(FIRST), IS_ALLOCATOR_AWARE(SECOND)>(f, s);
}

// swap implementation for Pair
template <class FIRST, class SECOND, bool firstaware, bool secondaware>
void swap(const Pair<FIRST,SECOND,firstaware,secondaware> &left,
				const Pair<FIRST,SECOND,firstaware,secondaware> &right) {
	left.swap(right);
}

// Declaration needed for GCC-based compilers
unsigned murmur_hash( const void * key, int len, unsigned seed );

// Pair hashing
template <class HASH_FIRST, class HASH_SECOND = HASH_FIRST>
struct pair_hash
{
	template <class FIRST, class SECOND, bool firstaware, bool secondaware>
	unsigned operator()(const Pair<FIRST, SECOND, firstaware, secondaware> &pair) const
	{
		HASH_FIRST hash_first;
		HASH_SECOND hash_second;
		const unsigned result[2] = { hash_first(pair.first), hash_second(pair.second) };
		const unsigned hash = murmur_hash(&result[0], sizeof(result), 0);
		return hash;
	}
};

} // namespace stingray_plugin_foundation
