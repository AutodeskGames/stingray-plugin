#pragma once

#include "platform.h"
#include "types.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Vector3 operator / (const Vector3 &lhs, const Vector3 &rhs);
__forceinline Vector3 operator * (const Vector3 &lhs, const Vector3 &rhs);
__forceinline Vector3 operator + (const Vector3 &lhs, const Vector3 &rhs);
__forceinline Vector3 operator - (const Vector3 &lhs, const Vector3 &rhs);
__forceinline void operator /= (Vector3 &lhs, const Vector3 &rhs);
__forceinline void operator *= (Vector3 &lhs, const Vector3 &rhs);
__forceinline void operator += (Vector3 &lhs, const Vector3 &rhs);
__forceinline void operator -= (Vector3 &lhs, const Vector3 &rhs);
__forceinline Vector3 operator - (const Vector3 &v);
__forceinline Vector3 operator + (const Vector3 &v);

__forceinline Vector3 operator / (const Vector3 &lhs, float rhs);
__forceinline Vector3 operator * (const Vector3 &lhs, float rhs);
__forceinline Vector3 operator * (float lhs, const Vector3 &rhs);
__forceinline Vector3 operator + (const Vector3 &lhs, float rhs);
__forceinline Vector3 operator - (const Vector3 &lhs, float rhs);
__forceinline void operator /= (Vector3 &lhs, float rhs);
__forceinline void operator *= (Vector3 &lhs, float rhs);
__forceinline void operator += (Vector3 &lhs, float rhs);
__forceinline void operator -= (Vector3 &lhs, float rhs);

__forceinline bool operator==(const Vector3 &lhs, const Vector3 &rhs);
__forceinline bool operator!=(const Vector3 &lhs, const Vector3 &rhs);
__forceinline bool operator< (const Vector3 &lhs, const Vector3 &rhs);
__forceinline bool operator<=(const Vector3 &lhs, const Vector3 &rhs);
__forceinline bool operator> (const Vector3 &lhs, const Vector3 &rhs);
__forceinline bool operator>=(const Vector3 &lhs, const Vector3 &rhs);

// Methods
__forceinline Vector3 vector3(float x, float y, float z);
__forceinline Vector3 vector3(const float v[3]);
__forceinline Vector3 vector3(const Vector2 &v);
__forceinline Vector3 vector3_base(int i);
__forceinline float & element(Vector3 &m, int i);
__forceinline const float & element(const Vector3 &m, int i);

__forceinline bool all_gt(const Vector3& p1, const Vector3& p2);
__forceinline bool all_lt(const Vector3& p1, const Vector3& p2);
__forceinline void zero(Vector3 &v);
__forceinline bool is_zero(const Vector3 &v);
__forceinline bool is_zero(const Vector3 &v, float eps);
__forceinline float length(const Vector3 &v);
__forceinline float length_squared(const Vector3 &v);
__forceinline float norm(const Vector3 &v);
__forceinline float one_norm(const Vector3 &v);
__forceinline float infinity_norm(const Vector3 &v);
__forceinline Vector3 normalize(const Vector3 &v);
__forceinline float dot(const Vector3 &v0, const Vector3 &v1);
__forceinline Vector3 cross(const Vector3 &v0, const Vector3 &v1);
__forceinline float distance(const Vector3 &v0, const Vector3 &v1);
__forceinline float distance_squared(const Vector3 &v0, const Vector3 &v1);
__forceinline Vector3 normal_vector(const Vector3 &v0,const Vector3 &v1, const Vector3& v2);
__forceinline Vector3 min(const Vector3 &v0, const Vector3 &v1);
__forceinline Vector3 max(const Vector3 &v0, const Vector3 &v1);

// Makes v orthonormal with respect to ref and returns the result.
__forceinline Vector3 orthonormalize(const Vector3 &v, const Vector3 &ref);

// Given unit vector x finds two other axes y and z so that an orthonormal coordinate
// system is formed.
__forceinline void make_axes(const Vector3 &x, Vector3 &y, Vector3 &z);

__forceinline Vector3 lerp(const Vector3 &a, const Vector3 &b, float t);

struct MagnitudeAndDirection
{
	float magnitude;
	Vector3 direction;
};
__forceinline MagnitudeAndDirection magnitude_and_direction(const Vector3 &v);

}

#include "vector3.inl"
