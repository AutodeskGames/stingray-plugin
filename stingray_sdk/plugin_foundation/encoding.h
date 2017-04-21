#pragma once

namespace stingray_plugin_foundation {

template<class T> class Array;
class Allocator;

// Functions for string encoding.
namespace encoding
{

// Encodes the unicode character `c` in UTF-8 at the position pointed
// to by `buffer`. `buffer` must have room for at least 5 bytes.
// Returns a pointer to the first character in buffer after the end of
// the encoding.
char *utf8_encode(int codepoint, char *utf8);

// Decodes the UTF-8 character at the start of `buffer` into a unicode
// code point and returns it in `res`. Returns a pointer to the first
// character in the buffer after the UTF-8 character that was just
// consumed.
const char *utf8_decode(const char *utf8, int &codepoint);

// Returns the number of bytes used by the UTF-8 codepoint pointed to by
// buffer. Advance by this amount to get to the next code point.
unsigned utf8_codepoint_bytes(const char *utf8);

// Decodes an UTF-8 string to a vector of codepoints.
void utf8_decode(const char *utf8, Array<unsigned> &codepoints);

// Encode a vector of codepoints to an array of UTF-8 characters.
void utf8_encode(const Array<unsigned> &codepoints, Array<char> &utf8);
// Encode an array of codepoints to an array of UTF-8 characters.
void utf8_encode(const unsigned *codepoints, unsigned size, Array<char> &utf8);

// Determines the begin and end position of the utf8 codepoint at
// `utf8`[index]. `end` is an index pointing to the byte after the
// utf-8 codepoint.
void utf8_location(const char *utf8, unsigned index, unsigned &begin, unsigned &end);

// Returns a pointer to the next character if the character at utf8 is valid, otherwise
// returns nullptr.
const char *utf8_valid_first(const char *utf8);

// Returns true if the string utf8 contains only valid UTF-8 code points and
// false otherwise.
bool utf8_valid_all(const char *utf8);

// Returns the number of of bytes needed to store the UCS-2 encoded wchar_t *
// as an UTF-8 value, including the zero byte at the end of the UTF-8 string.
unsigned wstr_to_utf8_bytes(const wchar_t *ucs2);

// Converts an UCS-2 encoded w_char * to an UTF-8 encoded char *.
// `size` specifies the size of the buffer. If the conversion requires
// more than `size` bytes, an assert is thrown.
void wstr_to_utf8(const wchar_t *ucs2, char *utf8, unsigned size);

// Converts an UCS-2 encoded w_char * to an UTF-8 encoded char *,
// allocating memory as necessary.
void wstr_to_utf8(const wchar_t *ucs2, Array<char> &utf8);

// Returns the number of of tokens needed to store the UTF-8 encoded char *
// as an UCS-2 value, including the zero token at the end of the UCS-2 string.
unsigned utf8_to_wstr_tokens(const char *utf8);

// Converts an UTF-8 encoded char * to an UCS-2 encoded wchar_t *.
// `tokens` specifies the number of tokens in the buffer. If the
// converted string contains more tokens, an assert is thrown.
void utf8_to_wstr(const char *utf8, wchar_t *ucs2, unsigned tokens);

// Converts an UTF-8 encoded char * to an UCS-2 encoded wchar_t *,
// allocating memory as necessary.
void utf8_to_wstr(const char *utf8, Array<wchar_t> &ucs2);

// Converts an UTF-8 encoded char * to an UCS-2 encoded wchar_t *,
// allocated using the specified allocator.
wchar_t *utf8_to_wstr(const char *utf8, Allocator &a);


} // namespace encoding

} // namespace stingray_plugin_foundation

#include "encoding.inl"
