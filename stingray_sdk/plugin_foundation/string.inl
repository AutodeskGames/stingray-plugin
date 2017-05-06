#include <ctype.h>

namespace stingray_plugin_foundation {

// ----------------------------------------------------------------------
// C string methods
// ----------------------------------------------------------------------

inline unsigned strlen32(const char *s)
{
	return (unsigned)strlen(s);
}

inline unsigned strlenw32(const wchar_t *s)
{
	const wchar_t *e = s;
	while (*e) ++e;
	return (unsigned)(e-s);
}

inline bool strequal(const char *s1, const char *s2)
{
	return strcmp(s1, s2) == 0;
}

inline bool strequali(const char *s1, const char *s2)
{
	while (*s1 && *s2) {
		if (*s1 != *s2) {
			if (tolower(*s1) != tolower(*s2))
				return false;
		}
		++s1; ++s2;
	}
	return *s1 == *s2;
}


inline bool strempty(const char *s)
{
	return *s == 0;
}

inline int to_int(const char *s)
{
	return (int)strtol(s, nullptr, 10);
}

inline float to_float(const char *s)
{
	return float(strtod(s, nullptr));
}

inline unsigned to_unsigned(const char *s)
{
	return (unsigned)strtoul(s, nullptr, 10);
}

inline int to_int(const char *s, bool &error)
{
	char *e;
	int i = (int)strtol(s, &e, 10);
	error = *s == 0 || *e != 0;
	return i;
}

inline float to_float(const char *s, bool &error)
{
	char *e;
	float f = float(strtod(s, &e));
	error = *s == 0 || *e != 0;
	return f;
}

inline unsigned to_unsigned(const char *s, bool &error)
{
	char *e;
	unsigned u = (unsigned)strtoul(s, &e, 10);
	error = *s == 0 || *e != 0;
	return u;
}

// ----------------------------------------------------------------------
// ConstString
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
// DynamicString
// ----------------------------------------------------------------------

inline void DynamicString::swap(DynamicString &other)
{
	_buffer.swap(other._buffer);
}

inline void append(DynamicString &str, const char *s)
{
	str.extend(strlen32(s));
	strcat(str.c_str(), s);
}

inline void append(DynamicString &str, const char *s, unsigned len)
{
	str.extend(len);
	strncat(str.c_str(), s, len);
}

inline void append(DynamicString &str, char c)
{
	str.extend(1);
	str.end()[-1] = c;
}

inline void prefix(DynamicString &str, const char *s)
{
	unsigned len = strlen32(s);
	str.extend(len);
	memmove(str.buffer().begin() + len, str.buffer().begin(), str.buffer().size() - len);
	memcpy(str.buffer().begin(), s, len);
}

// ----------------------------------------------------------------------
// string methods
// ----------------------------------------------------------------------

inline bool string::is_whitespace(char c)
{
	return c == '\t' || c == ' ' || c == '\n' || c == '\r';
}

inline const char *string::spaces(int n)
{
	const char *s =
		"          " "          " "          " "          " "          "
		"          " "          " "          " "          " "          "
		"          " "          " "          " "          " "          "
		"          " "          " "          " "          " "          ";
	if (n > 200)
		n = 200;
	return s + 200 - n;
}

inline bool string::contains(const char *s, const char *substring)
{
	return string::find(s, substring) != string::npos;
}

inline unsigned string::find_last(const char *s, char c)
{
	unsigned n = strlen32(s);
	for (int i=n - 1; i >= 0; --i) {
		if (s[i] == c)
			return i;
	}
	return npos;
}

inline unsigned string::find(const char *s, char c)
{
	unsigned n = strlen32(s);
	for (unsigned i=0; i<=n; ++i) {
		if (s[i] == c)
			return i;
	}
	return npos;
}

inline unsigned string::find(const char *s, const char *substring)
{
	unsigned n = strlen32(s) - strlen32(substring);
	if (n > 0x80000000)
		return npos;
	for (unsigned i=0; i<=n; ++i) {
		for (unsigned j=0;; ++j) {
			if (substring[j] == 0)
				return i;
			if (s[i+j] != substring[j])
				break;
		}
	}
	return npos;
}

inline void string::split(const char *s, const char *split_on, DynamicString &first, DynamicString &second)
{
	unsigned pos = find(s, split_on);
	if (pos == npos) {
		first = s;
		second.clear();
	} else {
		unsigned s_n = strlen32(s);
		unsigned split_on_n = strlen32(split_on);
		first.resize(pos);
		memmove(&first[0], &s[0], pos);
		second.resize(s_n - pos - split_on_n);
		memmove(&second[0], &s[pos + split_on_n], s_n - pos - split_on_n);
	}
}

// Cannot be defined in plugin_foundation at the moment. The Scaleform plugin
// includes string.h, and the plugin also removes the PS4 platform define,
// leading to __forceinline being undefined when compiling PS4. A fix is in the
// works. For now, defining this function in Wwise plugin (its only use)
// inline void string::split(const char *s, const char *split_by, Vector<DynamicString> &result)
// {
// 	Allocator & allocator = result.allocator();
// 	DynamicString a(allocator), b(allocator);
// 	string::split(s, split_by, a, b);
// 	while( !a.empty() ) {
// 		result.resize(result.size() + 1);
// 		result.back() = a;
// 		if( b.empty() )
// 			break;
// 		DynamicString temp = b;
// 		string::split(temp.c_str(), split_by, a, b);
// 	}
// }

// ----------------------------------------------------------------------

} // namespace stingray_plugin_foundation

