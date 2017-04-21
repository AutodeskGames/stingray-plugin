#pragma once

#include "platform.h"

#include <math.h>
#include <limits>
#include <float.h>

namespace stingray_plugin_foundation {

// Common math functions.
namespace math {
	const float pi = 3.141592654f;

	__forceinline bool is_pow2(unsigned);
	__forceinline float square_root(float);
	__forceinline float degrees_to_radians(float);
	__forceinline float radians_to_degrees(float f);

	#undef max
	template <class T> __forceinline T max(T a, T b);
	template <class T> __forceinline T max3(T a, T b, T c);

	#undef min
	template <class T> __forceinline T min(T a, T b);
	template <class T> __forceinline T min3(T a, T b, T c);

	template <class T> __forceinline T clamp(T x, T min, T max);

	template <class T> __forceinline T abs(T x);
	template <class T> __forceinline T sign(T x);

	unsigned branchless_max(unsigned a, unsigned b);
	unsigned branchless_min(unsigned a, unsigned b);

	unsigned div_ceil(unsigned a, unsigned b);
	unsigned div_round(unsigned a, unsigned b);

	__forceinline unsigned round_down_to_align(unsigned x, unsigned align)	{return x - x%align;}
	__forceinline unsigned round_up_to_align(unsigned x, unsigned align)	{return round_down_to_align(x+align-1, align);}

	__forceinline bool valid(const float *fa, unsigned n)
	{
		for (unsigned i=0; i<n; ++i) {
			float f = fa[i];
			if (f != f || f >= FLT_MAX || f <= -FLT_MAX)
				return false;
		}
		return true;
	}

	__forceinline unsigned log2(unsigned a)
	{
		unsigned log2 = 0;
		while(a >>= 1) log2++;
		return log2;
	}
}

__forceinline float lerp(float a, float b, float t);

// Finds the maximum value and its source from a number of tested
// values.
template <class SOURCE>
class FindMaximum
{
public:
	// Initiates the search for the maximum value.
	// * `start` The start value of the search.
	FindMaximum(float start = -std::numeric_limits<float>::max()) : _value(start) {}

	// Tests if value is the biggest value encountered so far.
	// If it is, the value and the source are recorded and the
	// function returns true, otherwise it returns false.
	bool test(float value, const SOURCE &source) {
		if (value > _value) {
			_value = value;
			_source = source;
			return true;
		} else
			return false;
	}

	// Returns true if any value bigger than the start value was
	// found.
	bool found(float start = -std::numeric_limits<float>::max()) {return _value > start;}

	// Returns the maximum value found.
	const float &value() {return _value;}

	// Returns the source of the maximum value found
	const SOURCE &source() {return _source;}

private:
	float _value;
	SOURCE _source;
};

// Finds the minimum value and its source from a number of tested
// values.
template <class SOURCE>
class FindMinimum
{
public:
	// Initiates the search for the minimum avlue.
	// * `start` The start value of the search
	FindMinimum(float start = std::numeric_limits<float>::max()) : _value(start) {}

	// Tests if value is the smallest value encountered so far.
	// If it is, the value and the source are recorded and the
	// function returns true, otherwise it returns false.
	bool test(const float &value, const SOURCE &source) {
		if (value < _value) {
			_value = value;
			_source = source;
			return true;
		} else
			return false;
	}

	// Returns true if any value smaller than the start value was
	// found.
	bool found(float start = std::numeric_limits<float>::max()) {return _value < start;}

	// Returns the maximum value found.
	const float &value() {return _value;}

	// Returns the source of the maximum value found
	const SOURCE &source() {return _source;}

private:
	float _value;
	SOURCE _source;
};

// Class that represents a cross fade.
// A cross fade is a mix between an in fade and an out fade.
class Crossfade
{
public:
	// Creates a new crossfade that is fully faded in.
	Crossfade() : _fade_in(1), _fade_in_t(FLT_MAX), _fade_out(0), _fade_out_t(FLT_MAX) {}

	// Creates a new crossfade that fades in over time `bt`.
	Crossfade(float bt) : _fade_in(0), _fade_in_t(bt), _fade_out(0), _fade_out_t(FLT_MAX) {}

	// Fades out the current crossfade over time bt.
	void fade_out(float bt) {
		if (bt < _fade_out_t)
			_fade_out_t = bt;
		if (_fade_in_t != FLT_MAX && bt < _fade_in_t)
			_fade_in_t = bt;
	}

	// Updates this crossfade
	void update(float dt);

	// Returns true if the crossfade is done
	bool is_done() {return _fade_out == 1;}

	// Returns the current blend value for the crossfade
	float blend() {return _fade_in - _fade_out;}

private:
	float _fade_in, _fade_in_t;
	float _fade_out, _fade_out_t;
};

}

#include "math.inl"
