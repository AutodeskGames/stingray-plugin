#pragma once

#include "string.h"
#include "vector.h"

namespace stingray_plugin_foundation {

// Convenience tools for manipulating paths.
namespace path
{
	// Strips the extension from path
	void strip_extension(DynamicString &path);

	// Strips the extension from `path` returns the result.
	DynamicString strip_extension(const char *path, Allocator &a);

	// Returns true if `path` has any extension.
	bool has_extension(const char *path);

	// Returns true if `path` has the specified extension. Extension comparison is case-insensitive.
	bool has_extension(const char *path, const char *pattern);

	// Joins `dir` to the beginning of all the file names in `files`.
	void join(const char *dir, const Vector<DynamicString> &files, Vector<DynamicString> &res);
}

}

namespace stingray_plugin_foundation {

namespace path {

	inline void strip_extension(DynamicString &path)
	{
		int n = path.size();
		for (int i = n - 1; i >= 0; --i) {
			if (path[i] == '.') {
				path.resize(i);
				return;
			}
		}
	}

	inline DynamicString strip_extension(const char *path, Allocator &a)
	{
		DynamicString s(a, path);
		strip_extension(s);
		return s;
	}

	inline bool has_extension(const char *path)
	{
		int n = strlen32(path);
		for (int i = n - 1; i >= 0; --i) {
			if (path[i] == '.')
				return true;
		}
		return false;
	}

	inline bool has_extension(const char *path, const char *pattern)
	{
		int n = strlen32(path);
		for (int i = n - 1; i >= 0; --i) {
			if (path[i] == '.') {
				return strequali(pattern, &path[i + 1]);
			}
		}
		return pattern[0] == '\0';
	}

} // namespace path

}
