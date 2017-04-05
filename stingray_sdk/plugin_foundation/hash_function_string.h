#pragma once

#include <stdint.h>
#include <string.h>
#include "string.h"
#include "hash_function.h"

namespace stingray_plugin_foundation {

struct string_hash
{
	unsigned operator()(const char *t) const {return hash32(t);}
	unsigned operator()(const ConstString &t) const {return hash32(t.c_str(), t.size());}
	unsigned operator()(const DynamicString &t) const {return hash32(t.c_str(), t.size());}
};

struct string_hash64
{
	uint64_t operator()(const char *t) const {return murmur_hash_64(t, strlen32(t),0);}
	uint64_t operator()(const ConstString &t) const {return murmur_hash_64(t.c_str(), t.size(),0);}
	uint64_t operator()(const DynamicString &t) const {return murmur_hash_64(t.c_str(), t.size(),0);}
};

} // namespace stingray_plugin_foundation
