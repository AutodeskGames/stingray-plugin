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

	// Returns true if 'c' is a directory separator character.
	bool is_directory_separator(char c);

	// Returns the length of the directory name pointed to by 'path'.
	unsigned directory_name_length(const char *path);

	// Returns the directory name pointed to by 'path'.
	DynamicString directory_name(const char *path, Allocator &a);

	// Joins 'dir' and 'file' with the proper path separator.
	DynamicString join(const char *dir, const char *file, Allocator &a);
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

	inline bool is_directory_separator(char c) {
		return c == '\\' || c == '/';
	}

	inline unsigned directory_name_length(const char *path) {
		int n = strlen32(path);
		for (int i = n - 1; i >= 0; --i) {
			if (is_directory_separator(path[i]))
				return i;
		}
		return 0;
	}

	inline DynamicString directory_name(const char *path, Allocator &a) {
		unsigned n = directory_name_length(path);
		return DynamicString(a, path, n);
	}

	inline DynamicString join(const char *dir, const char *file, Allocator &a) {
		DynamicString s(a);
		bool lhs_is_root = strequal(dir, "/");

		append(s, dir);

		if (s.size() > 0 && *file && !lhs_is_root)
			append(s, '\\');

		append(s, file);

		return s;
	}

} // namespace path

}
