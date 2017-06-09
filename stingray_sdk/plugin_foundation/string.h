#pragma once

#include "allocator.h"
#include "assert.h"

#include "array.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>

namespace stingray_plugin_foundation {

template <class T> class Vector;

// ----------------------------------------------------------------------
// Functions that extend the normal ANSI C string interface.
// ----------------------------------------------------------------------

// Returns the length of the string a 32-bit number (unsigned rather
// than size_t).
inline unsigned strlen32(const char *s);

// Returns the length of the string a 32-bit number (unsigned rather
// than size_t).
inline unsigned strlenw32(const wchar_t *s);

// Returns true if strings s1 and s2 are identical.
inline bool strequal(const char *s1, const char *s2);

// Returns true if strings s1 and s2 are identical when ignoring case.
// Only ascii characters (A-Z) are considered when comparing case.
bool strequali(const char *s1, const char *s2);

// Returns true if string s is empty.
inline bool strempty(const char *s);

// Converts s to an integer and returns the result.
inline int to_int(const char *s);

// Converts s to an unsigned and returns the result.
inline unsigned to_unsigned(const char *s);

// Converts s to a float and returns the result.
inline float to_float(const char *s);

// Converts s to an integer and returns the result.
inline int to_int(const char *s, bool &error);

// Converts s to an unsigned and returns the result.
inline unsigned to_unsigned(const char *s, bool &error);

// Converts s to a float and returns the result.
inline float to_float(const char *s, bool &error);

// ----------------------------------------------------------------------

// A thin wrapper around a const char * that just adds a == operator for string
// comparison. Note especially that it doesn't make a copy of the string. The
// original string pointer must be valid as long as this class is used.
//
// Typically, this class is used to make string comparisons easier to read
// and prevent mistakes. An example:
//
// 	ConstString s(p)
//		if (s == "open")
//			...
class ConstString
{
public:
	// ConstString that wraps the empty string.
	ConstString() : s("") {}

	// ConstString that wraps the specified string.
	ConstString(const char *s_) : s(s_) {}

	// Returns the raw string pointer.
	const char *c_str() const {return s;}

	// Returns true if the string is empty.
	bool empty() const {return *s == 0;}

	// Returns the length of the string
	unsigned size() const {return strlen32(s);}

	const char *s;
};

// Comparison operators for ConstString.
inline bool operator==(const ConstString &s1, const char *s2) {return strcmp(s1.s, s2) ==  0;}
inline bool operator==(const char *s1, const ConstString &s2) {return strcmp(s1, s2.s) ==  0;}
inline bool operator==(const ConstString &s1, const ConstString &s2) {return strcmp(s1.s, s2.s) == 0;}
inline bool operator!=(const ConstString &s1, const char *s2) {return strcmp(s1.s, s2) !=  0;}
inline bool operator!=(const char *s1, const ConstString &s2) {return strcmp(s1, s2.s) !=  0;}
inline bool operator!=(const ConstString &s1, const ConstString &s2) {return strcmp(s1.s, s2.s) != 0;}
inline bool operator<(const ConstString &s1, const char *s2) {return strcmp(s1.s, s2) <  0;}
inline bool operator<(const char *s1, const ConstString &s2) {return strcmp(s1, s2.s) <  0;}
inline bool operator<(const ConstString &s1, const ConstString &s2) {return strcmp(s1.s, s2.s) < 0;}

// ----------------------------------------------------------------------

// Class that represents a dynamic string -- a string whose content can be modified.
// This class is basically just a thin wrapper around an Array<char> buffer that stores
// the content of the string.
class DynamicString
{
public:
	ALLOCATOR_AWARE;

	// Creates a new dynamic string using the specified allocator.
	DynamicString(Allocator &a) : _buffer(a) {}

	// Creates a new dynamic string initialized from s.
	DynamicString(Allocator &a, const char *s) : _buffer(a) { unsigned length = s ? strlen32(s) : 0;  if (length > 0) { _buffer.resize(length + 1);  memmove(_buffer.begin(), s, _buffer.size()); } }

	// Creates a new dynamic string initialized from the first n characters of s.
	DynamicString(Allocator &a, const char *s, unsigned n) : _buffer(a) { if (n > 0) { _buffer.resize(n + 1);  memmove(_buffer.begin(), s, n); _buffer[n] = 0; } }

	// Copy constructor
	DynamicString(const DynamicString &o) : _buffer(o._buffer) {}

	// Assignment.
	void operator=(const char *s) { unsigned length = strlen32(s); if (length > 0) { _buffer.resize(length + 1); memmove(_buffer.begin(), s, _buffer.size()); } else _buffer.clear(); }

	// Assigns the characters from ds to this string. Does not change the allocator.
	void operator=(const DynamicString &ds) { _buffer = ds._buffer; }

	// Returns the size/length of the string. The size does not include the terminating zero.
	unsigned size() const {return _buffer.empty() ? 0 : _buffer.size() - 1;}

	// Returns true if the string is empty.
	bool empty() const {return size() == 0;}

	// Returns the C-string held by this dynamic string.
	char *c_str() { return _buffer.empty() ? empty_string() : _buffer.begin(); }
	const char *c_str() const {return _buffer.empty() ? empty_string() : _buffer.begin();}

	// Returns a pointer to the terminating zero at the end of C-string.
	char *end() { return _buffer.empty() ? c_str() : _buffer.end() - 1; }
	const char *end() const { return _buffer.empty() ? c_str() : _buffer.end() - 1; }

	// Accesses characters in the string.
	char &operator[](unsigned i) { return c_str()[i];}
	const char &operator[](unsigned i) const { return c_str()[i]; }

	// Resizes the string to the specified size (size does not include terminating zero).
	void resize(unsigned size) { bool empty = _buffer.empty(); _buffer.resize(size + 1); if (empty) _buffer[0] = '\0'; _buffer[size] = '\0'; }

	// Extends the string with the specified number of bytes.
	void extend(unsigned bytes) {resize(size() + bytes);}

	// Clears the memory and sets this string to the empty string.
	void clear() { _buffer.clear(); }

	// Returns the allocator of the string.
	Allocator &allocator() const {return _buffer.allocator();}

	// Swaps the contents efficiently.
	void swap(DynamicString &other);

	// Serializes the string to the stream
	template <class STREAM> void serialize(STREAM &s) {
		unsigned sz = size();
		s & sz;
		if (sz != size())
			resize(sz);

		if (sz != 0) {
			if (s.is_output())
				s.write(_buffer.begin(), sz);
			else
				s.read(_buffer.begin(), sz);
		}
	}

	Array<char> &buffer() { if (_buffer.empty()) _buffer.push_back(0); return _buffer; }
	private:
		// Raw access to the string buffer.
		Array<char> _buffer;
		static char *empty_string() { static char c = '\0'; return &c; }
};

// Comparison operators
inline bool operator==(const DynamicString &s1, const char *s2) {return strcmp(s1.c_str(), s2) ==  0;}
inline bool operator==(const char *s1, const DynamicString &s2) {return strcmp(s1, s2.c_str()) ==  0;}
inline bool operator==(const DynamicString &s1, const DynamicString &s2) {return strcmp(s1.c_str(), s2.c_str()) == 0;}
inline bool operator!=(const DynamicString &s1, const char *s2) {return strcmp(s1.c_str(), s2) !=  0;}
inline bool operator!=(const char *s1, const DynamicString &s2) {return strcmp(s1, s2.c_str()) !=  0;}
inline bool operator!=(const DynamicString &s1, const DynamicString &s2) {return strcmp(s1.c_str(), s2.c_str()) != 0;}
inline bool operator<(const DynamicString &s1, const char *s2) {return strcmp(s1.c_str(), s2) <  0;}
inline bool operator<(const char *s1, const DynamicString &s2) {return strcmp(s1, s2.c_str()) <  0;}
inline bool operator<(const DynamicString &s1, const DynamicString &s2) {return strcmp(s1.c_str(), s2.c_str()) < 0;}

// Appends `s` to the end of `str`.
inline void append(DynamicString &str, const char *s);

// Appends `c` to the end of `str`.
inline void append(DynamicString &str, char c);

// Appends `len` characters beginning from `s` to the end of `str`.
inline void append(DynamicString &str, const char *s, unsigned len);

// Inserts `s` in front of any characters in `str`.
inline void prefix(DynamicString &str, const char *s);

// ----------------------------------------------------------------------

// Namespace for string operations.
namespace string {

	const unsigned npos = UINT_MAX;

	// Returns true if c is a whitespace character.
	bool is_whitespace(char c);

	// Returns the index of the first occurrence of `c` in
	// `s` or `npos` if not found.
	unsigned find(const char *s, char c);

	// Returns the index of the last occurrence of `c` in
	// `s` or `npos` if not found.
	unsigned find_last(const char *s, char c);

	// Returns the index of the first occurrence of `substring` in
	// `s` or `npos` if not found.
	unsigned find(const char *s, const char *substring);

	// Returns the index of the last occurrence of `substring` in
	// `s` or `npos` if not found.
	unsigned find_last(const char *s, const char *substring);

	// Returns true if `s` contains `substring`.
	bool contains(const char *s, const char *substring);

	// Splits the string `s` on the first instance of `split_on` and stores the
	// results in `first` and `second`. If `split_on` is not found, `first`
	// will get the entire string.
	void split(const char *s, const char *split_on, DynamicString &first, DynamicString &second);

	// Splits the string `s` on all instances of `split_on` and stores the
	// results in `result`
	void split(const char *s, const char *split_by, Vector<DynamicString> &result);

	enum SkipEmpty { SKIP_EMPTY, DONT_SKIP_EMPTY };
	// Joins each string in `strings` into a single string separated by `separator` and stores the result in `result`.
	void join(const DynamicString* strings, unsigned num_strings, const char* separator, DynamicString& result, SkipEmpty skip_empty = DONT_SKIP_EMPTY);

	// Returns a pointer to a string with n spaces for indentation purposes. If n > 200 a string with 200 spaces
	// will be returned.
	const char *spaces(int n);

	// Returns true if s is a lowercase string.
	bool is_lowercase(const char *s);

	// Replaces the character range (start, start+size) in the string s with the
	// replacement rep.
	void replace(DynamicString &s, unsigned start, unsigned size, const char *rep);

	// Replaces the occurances of the string `find` with the replacement `rep` and returns the number of successful replacements made.
	unsigned replace_all(DynamicString &s, const char *find, const char *rep);

	// In-place converts the string to lower case
	void to_lower_case(char *s);

	// In-place converts the string to upper case
	void to_upper_case(char *s);

	// Converts from camel case to underscore representation.
	DynamicString from_camel_case(const char *s, Allocator &a);

	// Returns the string with the character stripped out.
	DynamicString strip(const char *s, char c, Allocator &a);

	// Trims whitespace from the start and end of the string and returns the result.
	DynamicString trim(const char *s, Allocator &a);

	// Returns a substring of s starting at start and of length.
	DynamicString substring(const char *s, unsigned start, unsigned length, Allocator &a);

	// Returns true if `str` contains `c`.
	bool in_string(const char *str, char c);

	// Returns true if `str` only contains characters in `allowed`.
	bool consists_of(const char *str, const char *allowed);

	// Returns true if `str` begins with `begins`.
	bool begins_with(const char *str, const char *begins);

	// Returns true if `str` ends with `ends`.
	bool ends_with(const char *str, const char *ends);
	bool ends_with(const wchar_t *str, const wchar_t *ends);

	// Returns a copy of the string `str` allocated with the allocator `a`.
	char* copy(const char *str, Allocator& a);

	// Copies src to dest. Truncates the copy if necessary so that more than
	// `dest_size` bytes are never written to `dest`. Always terminates
	// dest with a \0 character. Utf-8 characters are guaranteed to not get
	// truncated in the middle of a multibyte character.
	void copy(char *dest, const char *src, unsigned dest_size);
	void copy(wchar_t *dest, const wchar_t *src, unsigned dest_size);

	// Appends `src` to the end of `dest`. Truncates `dest` if necessary so that
	// more than `dest_size` bytes are never written to `dest`. Always terminates
	// dest with a \0 character. Utf-8 characters are guaranteed to not get
	// truncated in the middle of a multibyte character.
	void append(char *dest, const char *src, unsigned dest_size);
	void append(wchar_t *dest, const wchar_t *src, unsigned dest_size);

	#ifdef DEVELOPMENT
		// Returns a string allocated by `a` representing a typcial hex_view of the `data`.
		// (Such as shown by a memory debugger, for instance.)
		// `columns` is the number of columns of hex values in the view.
		// If `ascii_column` is true a column that shows ascii representation is included.
		DynamicString hex_view(Allocator &a, const char *data, unsigned size, unsigned columns = 16, bool ascii_column = true);
	#endif

} // namespace string

}

#include "string.inl"
