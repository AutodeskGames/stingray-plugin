#pragma once

#include <string.h>
#include "assert.h"
#include "platform.h"

// This file is the runtime representation of a config data structure. A config data structure
// is a JSON-like object for representing generic data. This format is suitable when the
// development cost of creating a custom binary format is big and the benefits are small.
// (I.e. for any data that is not massive bulk data -- such as small configuration files.)
//
// The runtime format is essential (type, data) where type is a four-byte type identifier
// and data is four bytes of data. We use four bytes for the type identifier for alignment
// purposes. Note that the runtime format represent an entire config object as a single
// memory block. Local pointers inside the memory block are used to build structure.
//
// Note that it is possible to optimize this format further to squeeze out a few more bytes.

namespace stingray_plugin_foundation {

struct ConstConfigArray;
struct ConstConfigObject;

namespace const_config
{
	// Type used for offset parameters
	typedef unsigned offset_t;

	// The supported value types
	enum ValueType {NIL, BOOL, INTEGER, FLOAT, STRING, ARRAY, OBJECT};

	// Generic representation of a value of one of the types.
	union Value {
		int b;
		int i;
		float f;
		offset_t s;		// Offset to char *
		offset_t a;		// Offset to ConstConfigArray *
		offset_t o;     // Offset toConstConfigObject *
	};
}

// Represents the root object (the first item in the memory block).
struct ConstConfigRoot
{
	int type;					// ValueType
	const_config::Value value;
};

// Represents an array. Note that the type is only stored once, all objects in an array
// must have the same type. In the memory layout, the ConstConfigArray block is followed
// by *size* data items (which are bool, int, float, etc) depending on type.
struct ConstConfigArray
{
	int type;							// ValueType
	int size;
	const_config::Value first_item;		// size data items follows in memory
};

// Represents an entry in a ConstConfigObject. Stores the key (always a string), the
// type of the entry and the value.
struct ConstConfigObjectEntry
{
	const_config::offset_t name;	// Offset to name
	int type;						// ValueType
	const_config::Value value;
};

// Represents an object. In the memory layout, ConstConfigObject is followed by
// *size* ConstConfigObjectEntry structures that contain the actual objects.
struct ConstConfigObject
{
	int size;
	ConstConfigObjectEntry first_entry;
};

// Convenience class used to access config data.
class ConstConfigItem
{
public:
	// Creates a nil config item.
	ConstConfigItem() : _base(nullptr), _type(const_config::NIL) {}

	// Creates a config item from the specified root.
	ConstConfigItem(const ConstConfigRoot &root) : _base((const char *)&root), _type(root.type), _value(root.value) {}

	// Creates a config item with the specified base, type and data.
	ConstConfigItem(const char *base, const_config::ValueType t, const_config::Value v) : _base(base), _type(t), _value(v) {}

	bool is_nil() const {return _type == const_config::NIL;}
	bool is_bool() const {return _type == const_config::BOOL;}
	bool is_false() const {return _type == const_config::BOOL && !_value.b;}
	bool is_true() const {return _type == const_config::BOOL && _value.b;}
	bool is_integer() const {return _type == const_config::INTEGER;}
	bool is_float() const {return _type == const_config::FLOAT;}
	bool is_number() const {return is_integer() || is_float();}
	bool is_string() const {return _type == const_config::STRING;}
	bool is_resource() const { return is_string() || is_object() && (*this)["$resource_name"].is_string(); }
	bool is_resource(const char *type) const { return is_resource() && (is_string() || (*this)["$resource_type"].is_string() && strcmp((*this)["$resource_type"].to_string(),type)==0); }
	bool is_array() const { return _type == const_config::ARRAY; }
	bool is_object() const {return _type == const_config::OBJECT;}

	bool to_bool() const	{XENSURE(is_bool()); return _value.b != 0;}
	int to_integer() const	{XENSURE(is_integer()); return _value.i;}
	float to_float() const	{return is_float() ? _value.f : float(to_integer());}
	const char *to_string() const {XENSURE(is_string()); return raw_s();}
	const char *to_resource(const char *type) const {
		XENSURE(is_resource(type));
		if (is_string()) {
			return to_string();
		}
		return (*this)["$resource_name"].to_string();
	}

	bool operator||(bool b) const {return is_bool() ? to_bool() : b;}
	int operator||(int i) const {return is_integer() ? _value.i : i;}
	unsigned operator||(unsigned i) const {return is_integer() ? unsigned(_value.i) : i;}
	float operator||(float f) const {return is_float() ? _value.f : (is_integer() ? _value.i : f);}
	const char *operator||(const char *s) const {return is_string() ? raw_s() : s;}
	ConstConfigItem operator||(ConstConfigItem o) {return is_nil() ? o : *this;}

	int size() const {return is_array() ? raw_a()->size : 0;}
	int n_items() const {return is_object() ? raw_o()->size : 0;}

	ConstConfigItem operator[](int i) const {
		if (!is_array())
			return ConstConfigItem();
		if (i<0 || i>=raw_a()->size)
			return ConstConfigItem();
		const ConstConfigArray &arr = *raw_a();
		return ConstConfigItem(_base, (const_config::ValueType)arr.type, *(&arr.first_item + i));
	}

	ConstConfigItem operator[](const char *s) const {
		if (!is_object())
			return ConstConfigItem();
		const ConstConfigObject &obj = *raw_o();
		for (int i=0; i<obj.size; ++i) {
			const ConstConfigObjectEntry &e = *(&obj.first_entry + i);
			if (strcmp(_base + e.name, s) == 0)
				return ConstConfigItem(_base, (const_config::ValueType)e.type, e.value);
		}
		return ConstConfigItem();
	}

	ConstConfigItem item(int i, const char **s = 0) const {
		if (!is_object())
			return ConstConfigItem();
		const ConstConfigObject &obj = *raw_o();
		if (i<0 || i>=obj.size)
			return ConstConfigItem();

		const ConstConfigObjectEntry &e = *(&obj.first_entry + i);
		if(s) *s = _base + e.name;
		return ConstConfigItem(_base, (const_config::ValueType)e.type, e.value);
	}

private:
	const char *raw_s() const {return _base + _value.s;}
	const ConstConfigArray *raw_a() const {return (ConstConfigArray *)(_base + _value.a);}
	const ConstConfigObject *raw_o() const {return (ConstConfigObject *)(_base + _value.o);}

	const char *_base;				// Base for offsets
	int _type;						// ValueType
	const_config::Value _value;
};

} // namespace stingray_plugin_foundation
