#pragma once
#include <stdio.h>
#include <stdint.h>

#include "platform.h"

namespace stingray_plugin_foundation {

#define ID32_FORMAT "#ID[%08x]"
#define ID64_FORMAT "#ID[%016llx]"

// An IdString64 is a 64-bit hash of a string value. It can be used
// instead of strings to save memory and processing time.
//
// If you know that the keyspace is small and want to save memory
// you can use an IdString32 instead of an IdString64. IdString32
// uses the same hash function as IdString64, but just keeps the
// first 32 bits of the hash so you can do a reverse lookup using
// the same tables.
class IdString64
{
public:
	IdString64();
	explicit IdString64(uint64_t id);
	explicit IdString64(const char *s);
	IdString64(const char *s, uint64_t id);
	IdString64(unsigned len, const char *s);

	// Returns the stored hash value.
	uint64_t id() const {return _id;}

	// True if this is the empty string.
	bool empty() const {return _id == 0;}

	// True if this is not the empty string.
	bool nonempty() const {return _id != 0;}

	bool operator==(const IdString64 &o) const {return _id == o._id;}
	bool operator!=(const IdString64 &o) const {return _id != o._id;}
	bool operator<(const IdString64 &o) const {return _id < o._id;}

	// Converts the id to a string on the format #ID[xxxxxxxxxxxxxxxx].
	// Returns a pointer to a static copy of the result. This will be
	// overwritten by next call.
	const char *to_string() const {return to_id_hex();}

	// Converts the id to a string on the format #ID[xxxxxxxxxxxxxxxx].
	// Returns a pointer to a static copy of the result. This will be
	// overwritten by next call.
	const char *to_id_hex() const;

	static const int HEX_BUFFER_SIZE = 17;

	// Writes a hexadecimal null terminated string to the memory pointed
	// to by `s`. There must be 17 bytes of allocated memory where `s`
	// is pointing.
	void to_hex(char *s) const {sprintf(s, "%016llx", (unsigned long long)_id);}

private:
	uint64_t _id;
};

// A 32 bit hashed string value. If your keyspace is too big and you
// get collisions with this hash, you should switch to an IdString64
// instead.
class IdString32
{
public:
	IdString32();
	explicit IdString32(unsigned id);
	explicit IdString32(uint64_t id64);
	explicit IdString32(const char *s);
	IdString32(const char *s, unsigned id);
	IdString32(unsigned len, const char *s);

	template <class STREAM> void serialize(STREAM &s) {
		s & _id;
	}

	// Returns the stored hash value.
	unsigned id() const {return _id;}

	// True if this is the empty string.
	bool empty() const {return _id == 0;}

	// True if this is not the empty string.
	bool nonempty() const {return _id != 0;}

	bool operator==(const IdString32 &o) const {return _id == o._id;}
	bool operator!=(const IdString32 &o) const {return _id != o._id;}
	bool operator<(const IdString32 &o) const {return _id < o._id;}

	const char *to_string() const {return to_id_hex();}
	const char *to_id_hex() const;
	static const int HEX_BUFFER_SIZE = 9;
	char *to_hex(char *s) const {sprintf(s, "%08x", _id); return s;}

private:
	unsigned _id;
};

struct idstring_hash {
	unsigned operator()(const IdString64 &t) const {return (t.id() >> 32);}
	unsigned operator()(const IdString32 &t) const {return t.id();}
};

}

#include "id_string.inl"
