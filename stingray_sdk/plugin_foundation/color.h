#pragma once

#include "platform.h"
#include "math.h"

namespace stingray_plugin_foundation {

typedef unsigned int Color8;

__forceinline Color8 color8(unsigned char a, unsigned char r, unsigned char g, unsigned char  b)
{
	return (a << 24) | (r << 16) | (g << 8) | b;
}

__forceinline unsigned char alpha(Color8 c) {return (c >> 24) & 0xff;}
__forceinline unsigned char red(Color8 c) 	{return (c >> 16) & 0xff;}
__forceinline unsigned char green(Color8 c) {return (c >>  8) & 0xff;}
__forceinline unsigned char blue(Color8 c) 	{return (c >>  0) & 0xff;}

__forceinline void set_alpha(Color8& c, unsigned char a) { c &= 0x00ffffff; c |= (a << 24); }

template<>
__forceinline Color8 lerp(const Color8& a, const Color8& b, float t) {
	return color8(
		lerp(alpha(a), alpha(b), t),
		lerp(red(a), red(b), t),
		lerp(blue(a), blue(b), t),
		lerp(green(a), green(b), t));
}

struct Color32 {
	float r, g, b, a;
};

} // namespace stingray_plugin_foundation
