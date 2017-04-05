#pragma once

#include "stream.h"
//#include "array.h"
#include "allocator.h"

// sourced from engine's data_compiler.h

namespace stingray_plugin_foundation {

namespace buffer
{
	//Buffer buffer(const Array<char> &resource, Allocator &allocator) {
	//	Buffer result;
	//	result.len = resource.size();
	//	result.p = (char *)allocator.allocate(result.len);
	//	memmove(result.p, resource.begin(), result.len);
	//	return result;
	//}

	//Buffer buffer(const Array<char> &header, const Array<char> &data, Allocator &allocator) {
	//	Buffer result;
	//	result.len = header.size() + data.size();
	//	XENSURE(result.len > 0);
	//	result.p = (char *)allocator.allocate(result.len);
	//	memcpy(result.p, header.begin(), header.size());
	//	memcpy(result.p + header.size(), data.begin(), data.size());
	//	return result;
	//}

	//Buffer buffer(const StringStream &os, Allocator &allocator) {
	//	Buffer result;
	//	result.p = (char *)allocator.allocate(os.size());
	//	result.len = os.size();
	//	memcpy(result.p, os.c_str(), os.size());
	//	return result;
	//}

	//Buffer buffer(MemoryOutputBuffer &ob, Allocator &allocator) {
	//	Buffer result;
	//	result.len = (unsigned)ob.position();
	//	result.p = (char *)allocator.allocate(result.len);
	//	ob.read(result.p);
	//	return result;
	//}

	//Buffer copy(Buffer b, Allocator &allocator)
	//{
	//	Buffer result;
	//	result.len = b.len;
	//	result.p = (char *)allocator.allocate(result.len);
	//	memcpy(result.p, b.p, result.len);
	//	return result;
	//}

	//template <class T> Buffer serialize(T &t, Allocator &allocator) {
	//	MemoryOutputBuffer mob(allocator);
	//	OutputArchive oa = SharedPtr<OutputBuffer>(mob);
	//	oa & t;
	//	return buffer(mob, allocator);
	//}

	template <class T> Buffer pack(T &t, Allocator &allocator) {
		Buffer result;
		result.len = sizeof(T);
		result.p = (char *)allocator.allocate(result.len);
		char *p = result.p;
		stream::pack(p, t);
		return result;
	}
} // namespace buffer

} // namespace stingray_plugin_foundation
