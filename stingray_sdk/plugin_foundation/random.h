#pragma once

#include "platform.h"
#include "math.h"

namespace stingray_plugin_foundation {

// A fast LCG random number generator. The numbers it produces are not completely
// random but it is faster and more random than vanilla C rand(). It should be good
// enough for most purposes.
class Random
{
	// This variable should NOT need to be volatile, but there is a bug in VC++. If
	// this variable is not volatile Vector3(random(), random(), random()) sets all
	// components to the same value.
	volatile unsigned _state;

public:
	static const unsigned A = 1664525 , B = 1013904223;

	__forceinline Random() : _state(0) {}
	__forceinline Random(unsigned s) : _state(s) {}
	__forceinline unsigned seed() const {return _state;}
	__forceinline void set_seed(unsigned s) {_state = s;}

	__forceinline void next() {_state = A * _state + B;}
	__forceinline unsigned rand_u32() {next(); return _state;}
	__forceinline double rand_double() {return double(rand_u32()) * (0.5 / 0x80000000);}
	__forceinline float rand_float() {return float(rand_u32()) * (0.5f / 0x80000000);}

	__forceinline double operator()(double max) {return max * rand_double();}
	__forceinline double operator()(double min, double max) {return min + (max - min)*rand_double();}

	__forceinline float operator()() {return rand_float();}
	__forceinline float operator()(float max) {return max * rand_float();}
	__forceinline float operator()(float min, float max) {return min + (max - min)*rand_float();}

	__forceinline int operator()(int max_plus_1)  {return (int)floor(max_plus_1*rand_double());}
	__forceinline int operator()(int min, int max) {return (int)floor(min + (max - min + 1)*rand_double());}

	__forceinline unsigned operator()(unsigned max_plus_1)  {return unsigned(max_plus_1*rand_double());}
	__forceinline unsigned operator()(unsigned min, unsigned max) {return unsigned(min + (max - min + 1)*rand_double());}

	// Convenience methods -- coin toss
	__forceinline bool heads() {return rand_float() < 0.5f;}
	__forceinline bool tails() {return rand_float() > 0.5f;}

	// Convenience methods -- random picking
	template <class T> __forceinline T &pick(T &t1, T &t2) {return rand_float() < 0.5f ? t1 : t2;}
	template <class T> __forceinline const T &pick(const T &t1, const T &t2) {return rand_float() < 0.5f ? t1 : t2;}
	template <class T> __forceinline T &pick( T &v ) {return v[ (*this)(v.size()) ];}
	template <class T> __forceinline const T &pick( const T &v ) {return v[ (*this)(v.size()) ];}

	// Random pick with weight. T must have "weight" field.
	template <class T> __forceinline T &pick_weighted( T &v ) {
		float sum = 0;
		typename T::iterator it, begin = v.begin(), end = v.end();
		for (it=begin; it<end; ++it)
			sum += it->weight;
		float pick = (*this)(sum);
		float acc = 0;
		for (it=begin; it<end; ++it) {
			acc += it->weight;
			if (pick < acc) return *it;
		}
		return v.back();
	}
	template <class T> __forceinline const T &pick_weighted( T &v ) {
		float sum = 0;
		typename T::const_iterator it, begin = v.begin(), end = v.end();
		for (it=begin; it<end; ++it)
			sum += it->weight;
		float pick = (*this)(sum);
		float acc = 0;
		for (it=begin; it<end; ++it) {
			acc += it->weight;
			if (pick < acc) return *it;
		}
		return v.back();
	}
};

}
