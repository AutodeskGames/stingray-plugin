#include <stdint.h>
#include "hash_function.h"
#include "array.h"

namespace stingray_plugin_foundation {

inline IdString64::IdString64() : _id(0)
{
}

inline IdString64::IdString64(uint64_t id) : _id(id)
{
}

inline IdString64::IdString64(const char *s)
{
	_id = murmur_hash_64(s, (unsigned)strlen(s), 0);
}

inline IdString64::IdString64(unsigned len, const char *s)
{
	_id = murmur_hash_64(s, len, 0);
}

inline IdString64::IdString64(const char *s, uint64_t id)
{
	_id = id;
	#if defined(_DEBUG) && defined(XASSERT)
		XASSERT(_id == murmur_hash_64(s, (unsigned)strlen(s), 0), "Bad static idstring `%s`", s);
	#endif
}

inline const char *IdString64::to_id_hex() const
{
	static char buffer[200];
	static char *p = &buffer[0];

	if (p + HEX_BUFFER_SIZE + 10 > &buffer[200])
		p = &buffer[0];
	char hex[HEX_BUFFER_SIZE];
	to_hex(hex);
	sprintf(p, "#ID[%s]", hex);
	char *s = p;
	p += strlen(p) + 1;
	return s;
}

inline IdString32::IdString32() : _id(0) {}
inline IdString32::IdString32(unsigned id) : _id(id) {}

inline IdString32::IdString32(const char *s)
{
	uint64_t id64 = murmur_hash_64(s, (unsigned)strlen(s), 0);
	_id = (id64 >> 32);
}

inline IdString32::IdString32(unsigned len, const char *s)
{
	uint64_t id64 = murmur_hash_64(s, len, 0);
	_id = (id64 >> 32);
}

inline const char *IdString32::to_id_hex() const
{
	static char buffer[200];
	static char *p = &buffer[0];

	if (p + HEX_BUFFER_SIZE + 10 > &buffer[200])
		p = &buffer[0];
	char hex[HEX_BUFFER_SIZE];
	to_hex(hex);
	sprintf(p, "#ID[%s]", hex);
	char *s = p;
	p += strlen(p) + 1;
	return s;
}

template <>
template <class STREAM> void Array<IdString64>::serialize(STREAM &stream) {
	raw_array_serialize(stream, *this);
}

template <>
template <class STREAM> void Array<IdString32>::serialize(STREAM &stream) {
	raw_array_serialize(stream, *this);
}

}
