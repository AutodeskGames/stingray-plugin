#pragma once

#include "platform.h"

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

struct Color32 {
	float r, g, b, a;
};

} // namespace stingray_plugin_foundation
