#pragma once

#include "array.h"

#include <string.h>

namespace stingray_plugin_foundation {

// Functions for treating a Array<char> or a char * as a memory stream that can be written to
// and read from.
namespace stream {

	// Packs the data in t to the stream.
	template <class T> void pack(char *&v, const T &t)
	{
		memmove(v, &t, sizeof(T));
		v += sizeof(T);
	}

	// Packs the data in t to the stream, resizing it if necessary.
	template <class T> void pack(Array<char> &v, const T &t)
	{
		v.resize(v.size() + sizeof(T));
		memmove(&v[0] + v.size() - sizeof(T), &t, sizeof(T));
	}

	// Patches already packed data at the specified location.
	template <class T> void patch(char *&v, const T &t)
	{
		memmove(v, &t, sizeof(T));
		v += sizeof(T);
	}

	// Patches already packed data at the specified offset.
	template <class T> void patch(Array<char> &v, unsigned &offset, const T &t)
	{
		memmove(&v[0] + offset, &t, sizeof(T));
		offset += sizeof(T);
	}

	// Packs `count` bytes from `p` to the stream.
	inline void pack_bytes(char *&v, const void *p, unsigned count)
	{
		memmove(v, p, count);
		v += count;
	}

	// Packs `count` bytes from `p` to the stream, resizing it if necessary.
	inline void pack_bytes(Array<char> &v, const void *p, unsigned count)
	{
		v.resize(v.size() + count);
		memmove(&v[0] + v.size() - count, p, count);
	}

	// Packs `count` zero bytes to the stream.
	inline void pack_zeroes(char *&v, unsigned count)
	{
		memset(v, 0, count);
		v += count;
	}

	// Packs `count` zero bytes to the stream, resizing it if necessary.
	inline void pack_zeroes(Array<char> &v, unsigned count)
	{
		v.resize(v.size() + count);
		memset(&v[0] + v.size() - count, 0, count);
	}

	// Aligns the stream to the specified alignment.
	inline void pack_align(Array<char> &v, unsigned align) {
		while (v.size() % align != 0)
			v.push_back(0);
	}

	// Unpacks an object of type T from the stream and returns it. The stream
	// pointer is advanced to the next object. Note that since this operation
	// only casts the pointer, it can have alignment problems if objects in the
	// stream are not aligned. To unpack potentially unaligned objects, use the
	// call unpack(stream, t) instead.
	template <class T> const T &unpack(const char *&stream)
	{
		const T* t = (const T *)stream;
		stream += sizeof(T);
		return *t;
	}

	template <class T> T &unpack(char *&stream)
	{
		T* t = (T *)stream;
		stream += sizeof(T);
		return *t;
	}


	// Unpacks an object of type T from the stream into the varaible t.
	template <class T> void unpack(const char *&stream, T &t)
	{
		memmove(&t, stream, sizeof(T));
		stream += sizeof(T);
	}

	template <class T> void unpack(char *&stream, T &t)
	{
		memmove(&t, stream, sizeof(T));
		stream += sizeof(T);
	}

	// Unpacks count raw bytes from the stream into `p` and returns them.
	// The stream pionter is advanced to beyond the bytes.
	inline void unpack_bytes(char *&stream, void *p, unsigned count)
	{
		memmove(p, stream, count);
		stream += count;
	}

	// Aligns the stream to the specified alignment.
	inline void unpack_align(char *&stream, unsigned align)
	{
		unsigned skip = (align - (uintptr_t)stream % align) % align;
		stream += skip;
	}

} // namespace stream

} // namespace stingray_plugin_foundation
