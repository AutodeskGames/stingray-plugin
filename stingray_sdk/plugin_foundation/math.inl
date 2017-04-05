#include "assert.h"

namespace stingray_plugin_foundation {

__forceinline bool math::is_pow2(unsigned x)
{
	return (x & (x - 1)) == 0;
}

__forceinline float math::square_root(float f)
{
	return sqrtf(f);
}

__forceinline float math::degrees_to_radians(float f)
{
	return f / 180.0f * pi;
}

__forceinline float math::radians_to_degrees(float f)
{
	return 180.0f * f / pi;
}

template <class T> __forceinline T math::max(T a, T b)
{
	return a > b ? a : b;
}

template <class T> __forceinline T math::max3(T a, T b, T c)
{
	return max(a, max(b,c));
}

template <class T> __forceinline T math::min(T a, T b)
{
	return a < b ? a : b;
}

template <class T> __forceinline T math::min3(T a, T b, T c)
{
	return min(a, min(b,c));
}


template <class T> __forceinline T math::clamp(T x, T min, T max)
{
	if(x>max)
		return max;
	else if(x<min)
		return min;
	else
		return x;
}

template <class T> __forceinline T math::abs(T x)
{
	if (x > 0)
		return x;
	else
		return -x;
}

template <class T> __forceinline T math::sign(T x)
{
	if (x > 0)
		return T(1);
	else if (x == 0)
		return T(0);
	else
		return T(-1);
}

__forceinline unsigned math::branchless_max(unsigned a, unsigned b)
{
	return a - ((a-b) & (a-b)>>31);
}

__forceinline unsigned math::branchless_min(unsigned a, unsigned b)
{
	return b + ((a-b) & (a-b)>>31);
}

__forceinline unsigned math::div_ceil(unsigned a, unsigned b) {
	return (a+b-1)/b;
}

__forceinline unsigned math::div_round(unsigned a, unsigned b) {
	return (a+b/2)/b;
}

__forceinline float lerp(float a, float b, float p)
{
	return a * (1-p) + b * p;
}

inline void Crossfade::update(float dt)
{
	if (_fade_in_t < FLT_MAX) {
		_fade_in += (1 - _fade_in) * dt / _fade_in_t;
		_fade_in_t -= dt;
		if (_fade_in_t <= 0) {
			_fade_in_t = FLT_MAX;
			_fade_in = 1;
		}
	}

	if (_fade_out_t < FLT_MAX) {
		_fade_out += (1 - _fade_out) * dt / _fade_out_t;
		_fade_out_t -= dt;
		if (_fade_out_t <= 0) {
			_fade_out_t = FLT_MAX;
			_fade_out = 1;
		}
	}

	XENSURE(blend() >= 0.0f);
}

}
