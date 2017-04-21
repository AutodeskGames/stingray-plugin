#pragma once

#include "allocator.h"
#include "array.h"
#include "platform.h"

namespace stingray_plugin_foundation {

class StringStream
{
public:
	StringStream(Allocator &a);
	StringStream &operator<<(char c);
	StringStream &operator<<(char *s);
	StringStream &operator<<(const char *s);
	StringStream &operator<<(wchar_t *s);
	StringStream &operator<<(const wchar_t *s);
	StringStream &operator<<(double d);
	StringStream &operator<<(float f);
	StringStream &operator<<(int i);
	StringStream &operator<<(unsigned u);
	StringStream &operator<<(uint64_t u);
	template <class T> StringStream &operator<<(T t) {t.other_types_are_not_allowed(); return *this;}

	// As regular printf, but prints to string stream.
	StringStream &printf(const char *format, ...);

	// Push a chunk of non null terminated data to the stream.
	StringStream &push(const char *data, unsigned int size);

	// Allocates size bytes of data at the end of the stream and returns a pointer for filling it.
	char *allocate(unsigned int size);

	// Logs a hex dump of the data to the string stream.
	StringStream &hex_dump(const char *p, unsigned size, int columns=16);

	void set_capacity(unsigned s);

	// Pads with spaces to arrive at the specified column.
	void indent(unsigned column);

	// Adds a multi-line string so each line, padded with spaces, begins at the specified column `column` and returns the number of lines that was added;
	unsigned add_indented_lines(unsigned column, const char* lines);

	// Adds the specified number of spaces.
	void add_spaces(unsigned n);

	const char *c_str() const;
	unsigned size() const;
	void clear() {_buffer.clear();}

private:
	mutable Array<char> _buffer;
};

} // namespace stingray_plugin_foundation

#include "string_stream.inl"
