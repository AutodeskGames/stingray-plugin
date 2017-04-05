#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "encoding.h"

namespace stingray_plugin_foundation {

inline StringStream::StringStream(Allocator &a) : _buffer(a) {}

inline StringStream & StringStream::operator<<(char c)
{
	_buffer.push_back(c);
	return *this;
}

inline StringStream &StringStream::operator<<(const char *s)
{
	int end = _buffer.size();
	int n = (int)strlen(s);
	_buffer.resize(end + n);
	if (n > 0)
		memmove(&_buffer[end], s, n);
	return *this;
}

inline StringStream &StringStream::operator<<(char *s)
{
	int end = _buffer.size();
	int n = (int)strlen(s);
	_buffer.resize(end + n);
	if (n > 0)
		memmove(&_buffer[end], s, n);
	return *this;
}

inline StringStream &StringStream::operator<<(const wchar_t *s)
{
	while (*s) {
		char utf8[6];
		*encoding::utf8_encode(*s, utf8) = 0;
		(*this) << utf8;
		++s;
	}
	return *this;
}

inline StringStream &StringStream::operator<<(wchar_t *s)
{
	while (*s) {
		char utf8[6];
		*encoding::utf8_encode(*s, utf8) = 0;
		(*this) << utf8;
		++s;
	}
	return *this;
}

inline StringStream &StringStream::operator<<(double d)
{
	char buffer[64];
	sprintf(buffer, "%.17g", d);
	(*this) << buffer;
	return *this;
}

inline StringStream &StringStream::operator<<(float f)
{
	char buffer[20];
	sprintf(buffer, "%.9g", f);
	(*this) << buffer;
	return *this;
}

inline StringStream &StringStream::operator<<(int i)
{
	char buffer[20];
	sprintf(buffer, "%i", i);
	(*this) << buffer;
	return *this;
}

inline StringStream &StringStream::operator<<(unsigned u)
{
	char buffer[20];
	sprintf(buffer, "%u", u);
	(*this) << buffer;
	return *this;
}

inline StringStream &StringStream::operator<<(uint64_t u)
{
	char buffer[20];
	sprintf(buffer, "%016" "llx", u);
	(*this) << buffer;
	return *this;
}

inline void StringStream::set_capacity(unsigned s)
{
	_buffer.set_capacity(s);
}

inline const char *StringStream::c_str() const
{
	_buffer.push_back(0);
	_buffer.pop_back();
	return _buffer.begin();
}

inline unsigned StringStream::size() const
{
	return _buffer.size();
}

} // namespace stingray_plugin_foundation
