#pragma once

#include <plugin_foundation/types.h>

namespace stingray_plugin_foundation {

// Conversion from float to half (fp16)
// This code comes from openEXR: http://www.openexr.com

/*
	Copyright (c) 2002-2011, Industrial Light & Magic, a division of Lucasfilm
	Entertainment Company Ltd. All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice, this list
	  of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright notice, this
	  list of conditions and the following disclaimer in the documentation and/or other
	  materials provided with the distribution.

	* Neither the name of Industrial Light & Magic nor the names of its contributors
	  may be used to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
	CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
	INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
	OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
	EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

namespace half_globals {
	static unsigned short _half_lookup[512];
	void init();
	union uif {
		unsigned int i;
		float f;
	};
	half special_case_convert(int i);
}

__forceinline half float_to_half(float v) {
	if (v==0.f) return 0;

	half_globals::uif x;
	x.f = v;

	int e = (x.i >> 23) & 0x000001ff;
	e = half_globals::_half_lookup[e];

	if( e )
		return e + (((x.i & 0x007fffff) + 0x00001000) >> 13);
	else
		return half_globals::special_case_convert(x.i);
}

// Implementation from http://fgiesen.wordpress.com/2012/03/28/half-to-float-done-quic/
__forceinline float half_to_float(half h)
{
	static const half_globals::uif magic = { (127 + (127 - 15)) << 23 };
	static const half_globals::uif was_infnan = { (127 + 16) << 23 };
	half_globals::uif o;

	o.i = (h & 0x7fff) << 13;	// exponent/mantissa bits
	o.f *= magic.f;				// exponent adjust
	if (o.f >= was_infnan.f)	// make sure Inf/NaN survive
		o.i |= 255 << 23;
	o.i |= (h & 0x8000) << 16;	// sign bit

	return o.f;
}

} // namespace stingray_plugin_foundation

#include "half.inl"
