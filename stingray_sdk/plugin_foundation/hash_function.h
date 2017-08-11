#pragma once

#include <stdint.h>
#include <string.h>

namespace stingray_plugin_foundation {

// Implementation of the 64 bit murmur hash function
// http://murmurhash.googlepages.com/
inline uint64_t murmur_hash_64(const void * key, int len, uint64_t seed)
{
	const uint64_t m = 0xc6a4a7935bd1e995ULL;
	const int r = 47;

	uint64_t h = seed ^ (len * m);

	const uint64_t * data = (const uint64_t *)key;
	const uint64_t * end = data + (len/8);

	while(data != end)
	{
		#if defined(ANDROID) || defined(IOS) || defined(WEB) // Unaligned 64bit reads not supported!
			uint64_t k;
			char *p = (char *)&k, *d = (char *)data;
			p[0] = d[0]; p[1] = d[1]; p[2] = d[2]; p[3] = d[3];
			p[4] = d[4]; p[5] = d[5]; p[6] = d[6]; p[7] = d[7];
			data++;
		#elif defined(WINDOWSPC) || defined(UWP) || defined(XBOXONE) || defined(__ORBIS__) || defined(MACOSX) || defined(LINUXPC)
			uint64_t k = *data++;
		#else
			#error Unaligned 64bit reads undefined!
		#endif

		k *= m;
		k ^= k >> r;
		k *= m;

		h ^= k;
		h *= m;
	}

	const unsigned char * data2 = (const unsigned char*)data;

	switch(len & 7)
	{
	case 7: h ^= uint64_t(data2[6]) << 48;
	case 6: h ^= uint64_t(data2[5]) << 40;
	case 5: h ^= uint64_t(data2[4]) << 32;
	case 4: h ^= uint64_t(data2[3]) << 24;
	case 3: h ^= uint64_t(data2[2]) << 16;
	case 2: h ^= uint64_t(data2[1]) << 8;
	case 1: h ^= uint64_t(data2[0]);
			h *= m;
	};

	h ^= h >> r;
	h *= m;
	h ^= h >> r;

	return h;
}

inline uint64_t hash64(const char *s)
{
	return murmur_hash_64(s, int(strlen(s)), 0);
}

inline unsigned hash32(const char *s)
{
	uint64_t id64 = murmur_hash_64(s, int(strlen(s)), 0);
	return unsigned(id64 >> 32);
}

inline unsigned hash32(const void * key, int len)
{
	uint64_t id64 = murmur_hash_64(key, len, 0);
	return unsigned(id64 >> 32);
}

// A quick hash for four byte sized values based on a single
// iteration of the murmur hash function.
//
// Another option would be to convert the bit pattern directly to
// an int. That would be faster, but might lead to clustering if
// the input values do not distribute evenly.
inline unsigned int four_byte_hash(const void * key)
{
	const unsigned int m = 0x5bd1e995;
	const int r = 24;
	unsigned int k = *(unsigned int *)key;

	k *= m;
	k ^= k >> r;
	k *= m;
	return k;
}

inline uint64_t eight_byte_hash_64(const void * key)
{
	const uint64_t m = 0xc6a4a7935bd1e995ULL;
	const int r = 47;
	uint64_t k = *(const uint64_t *)key;

	k *= m;
	k ^= k >> r;
	k *= m;
	return k;
}

// Default hashing for builtin-types.
template <class T> struct default_hash
{
	static constexpr bool value = false;
	unsigned operator()(T t) const { static_assert(value, "default_hash not implemented for this type!"); return 0; }
};

template <class T> struct default_hash<T *>
{
	unsigned operator()(T *t) const
	{
		#ifdef PLATFORM_64BIT
			return (unsigned)eight_byte_hash_64(&t);
		#else
			return four_byte_hash(&t);
		#endif
	}
};

template <class T> struct default_hash<const T *>
{
	unsigned operator()(const T *t) const
	{
		#ifdef PLATFORM_64BIT
			return (unsigned)eight_byte_hash_64(&t);
		#else
			return four_byte_hash(&t);
		#endif
	}
};

template <> struct default_hash<unsigned>
{
	unsigned operator()(unsigned t) const { return four_byte_hash(&t); }
};

template <> struct default_hash<int>
{
	unsigned operator()(int t) const { return four_byte_hash(&t); }
};

template <> struct default_hash<uint64_t>
{
	unsigned operator()(uint64_t t) const { return hash32(&t, sizeof(t)); }
};

template <> struct default_hash<int64_t>
{
	unsigned operator()(int64_t t) const { return hash32(&t, sizeof(t)); }
};

// Utility functions
inline uint64_t mix(uint64_t h, uint64_t k)
{
	const uint64_t m = 0xc6a4a7935bd1e995ULL;
	const int r = 47;

	k *= m;
	k ^= k >> r;
	k *= m;

	h ^= k;
	h *= m;

	return h;
}

inline unsigned mix(unsigned h, unsigned k)
{
	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	k *= m;
	k ^= k >> r;
	k *= m;

	h *= m;
	h ^= k;

	return h;
}

inline uint32_t entity_component_property_key(const char *s)
{
	uint32_t hash = 0;
	const char *key_start = s;
	while (*s) {
		if (*s == '.') {
			hash = mix(hash, hash32(key_start, (int)(s - key_start)));
			key_start = s + 1;
		}
		++s;
	}
	hash = mix(hash, hash32(key_start, (int)(s - key_start)));
	return hash;
}

} // namespace stingray_plugin_foundation
