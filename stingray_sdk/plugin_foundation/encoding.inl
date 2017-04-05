#include "assert.h"
#include "array.h"
#include <wchar.h>
#include <string.h>

namespace stingray_plugin_foundation {

inline char *encoding::utf8_encode(int c, char *utf8)
{
	if (c<0x80) {
		*utf8 = c;
		return utf8 + 1;
	} else if (c<0x800) {
		utf8[0] = (c>>6)|0xC0;
		utf8[1] = (c&0x3F)|0x80;
		return utf8 + 2;
	} else if (c<0x10000) {
		utf8[0] = (c>>12)|0xE0;
		utf8[1] = ((c>>6)&0x3F)|0x80;
		utf8[2] = (c&0x3F)|0x80;
		return utf8 + 3;
	} else if (c<0x110000) {
		utf8[0] = (c>>18)|0xf0;
		utf8[1] = ((c>>12)&0x3F)|0x80;
		utf8[2] = ((c>>6)&0x3F)|0x80;
		utf8[3] = (c&0x3F)|0x80;
		return utf8 + 4;
	} else {
		XERROR("Cannot encode character");
	}
	return utf8;
}

inline const char *encoding::utf8_decode(const char *utf8, int &codepoint)
{
	char c = *utf8;
	if ((c&0x80)==0x0) {
		codepoint = c;
		return utf8 + 1;
	} else if ((c&0xE0)==0xC0) {
		unsigned char d = utf8[1];
		XASSERT((d&0xC0)==0x80, "Archive not utf-8 encoded %s", utf8);
		codepoint = (static_cast<int>(c&0x1F)<<6) | static_cast<int>(d&0x3F);
		return utf8 + 2;
	} else if ((c&0xF0)==0xE0) {
		const char *d = utf8 + 1;
		XASSERT(((d[0]&0xC0)==0x80) && ((d[1]&0xC0)==0x80), "Archive not utf-8 encoded %s", utf8);
		codepoint = (static_cast<int>(c&0x0f)<<12) | (static_cast<int>(d[0]&0x3f)<<6) |
			static_cast<int>(d[1]&0x3f);
		return utf8 + 3;
	} else if ((c&0xf8)==0xf0) {
		const char *d = utf8 + 1;
		XASSERT(((d[0]&0xc0)==0x80) && ((d[1]&0xc0)==0x80) &&
			((d[2]&0xc0)==0x80), "Archive not utf-8 encoded %s", utf8);
		codepoint = (static_cast<int>(c&0x07)<<18) | (static_cast<int>(d[0]&0x3f)<<12) |
			(static_cast<int>(d[1]&0x3f)<<6) | static_cast<int>(d[2]&0x3f);
		return utf8 + 4;
	} else {
		XERROR("Archive not utf-8 encoded %s", utf8);
		return utf8;
	}
}

inline unsigned encoding::utf8_codepoint_bytes(const char *buffer)
{
	char c = *buffer;
	if ((c&0x80)==0x0)
		return 1;
	else if ((c&0xE0)==0xC0)
		return 2;
	else if ((c&0xF0)==0xE0)
		return 3;
	else if ((c&0xf8)==0xf0)
		return 4;
	else {
		XERROR("Length on part of utf-8 character");
		return 1;
	}
}

inline void encoding::utf8_decode(const char *utf8, Array<unsigned> &codepoints)
{
	while (*utf8) {
		int c;
		utf8 = utf8_decode(utf8, c);
		codepoints.push_back((unsigned)c);
	}
}

inline void encoding::utf8_encode(const Array<unsigned> &codepoints, Array<char> &utf8)
{
	utf8_encode(codepoints.begin(), codepoints.size(), utf8);
}

inline void encoding::utf8_encode(const unsigned *codepoints, unsigned size, Array<char> &utf8)
{
	const unsigned *it(codepoints), *end(codepoints + size);
	for(; it != end; ++it) {
		utf8.reserve(utf8.size() + 4);
		const char *new_ptr = utf8_encode(*it, utf8.end());
		utf8.resize((unsigned)(new_ptr - utf8.begin()));
	}
}

inline void encoding::utf8_location(const char *utf8, unsigned index, unsigned &begin, unsigned &end)
{
	XASSERT(index < strlen(utf8), "Index out of string");
	// walk backwards to find beginning of utf8 character
	begin = index;
	while(true) {
		if (begin == 0)
			break;
		if ((utf8[begin] & 0xc0) != 0x80)
			break;
		--begin;
	}
	end = begin + utf8_codepoint_bytes(utf8 + begin);
}

inline const char * encoding::utf8_valid_first(const char *utf8)
{
	char c = *utf8;
	const char *d = utf8 + 1;

	if ((c&0x80)==0x0)			return utf8 + 1;
	else if ((c&0xE0)==0xC0) 	return (d[0]&0xC0)==0x80 ? utf8+2 : nullptr;
	else if ((c&0xF0)==0xE0)	return (d[0]&0xC0)==0x80 && (d[1]&0xC0)==0x80 ? utf8+3 : nullptr;
	else if ((c&0xf8)==0xf0)	return (d[0]&0xc0)==0x80 && (d[1]&0xc0)==0x80 && (d[2]&0xc0)==0x80 ? utf8+4 : nullptr;
	else						return nullptr;
}

inline bool encoding::utf8_valid_all(const char *utf8)
{
	while (*utf8) {
		utf8 = utf8_valid_first(utf8);
		if (!utf8)
			return false;
	}
	return true;
}

inline unsigned encoding::wstr_to_utf8_bytes(const wchar_t *ucs2)
{
	char buffer[5];
	unsigned size = 0;
	while (*ucs2) {
		size += (unsigned)(utf8_encode(*ucs2, &buffer[0]) - &buffer[0]);
		++ucs2;
	}
	++size;
	return size;
}

inline void encoding::wstr_to_utf8(const wchar_t *ucs2, char *utf8, unsigned size)
{
	char *b = utf8;
	while (*ucs2) {
		b = utf8_encode(*ucs2, b);
		++ucs2;
	}
	XENSURE(unsigned(b - utf8) < size);
	*b = 0;
}

inline void encoding::wstr_to_utf8(const wchar_t *ucs2, Array<char> &utf8)
{
	unsigned n = wstr_to_utf8_bytes(ucs2);
	utf8.resize(n);
	wstr_to_utf8(ucs2, utf8.begin(), n);
}

inline unsigned encoding::utf8_to_wstr_tokens(const char *utf8)
{
	unsigned tokens = 0;
	while (*utf8) {
		++tokens;
		utf8 += utf8_codepoint_bytes(utf8);
	}
	++tokens;
	return tokens;
}

inline void encoding::utf8_to_wstr(const char *utf8, wchar_t *ucs2, unsigned tokens)
{
	wchar_t *b = ucs2;
	while (*utf8) {
		int c;
		utf8 = utf8_decode(utf8, c);
		*b = c;
		++b;
	}
	XENSURE(unsigned(b - ucs2) < tokens);
	*b = 0;
}

inline void encoding::utf8_to_wstr(const char *utf8, Array<wchar_t> &ucs2)
{
	unsigned n = utf8_to_wstr_tokens(utf8);
	ucs2.resize(n);
	utf8_to_wstr(utf8, ucs2.begin(), n);
}

inline wchar_t *encoding::utf8_to_wstr(const char *utf8, Allocator &a)
{
	unsigned n = utf8_to_wstr_tokens(utf8);
	wchar_t *res = (wchar_t *)a.allocate(sizeof(wchar_t)*n);
	utf8_to_wstr(utf8, res, n);
	return res;
}

} // namespace stingray_plugin_foundation
