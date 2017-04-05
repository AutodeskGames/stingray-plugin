#pragma once

#include "platform.h"
#include "types.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Vector2 operator / (const Vector2 &lhs, const Vector2 &rhs);
__forceinline Vector2 operator * (const Vector2 &lhs, const Vector2 &rhs);
__forceinline Vector2 operator + (const Vector2 &lhs, const Vector2 &rhs);
__forceinline Vector2 operator - (const Vector2 &lhs, const Vector2 &rhs);
__forceinline void operator /= (Vector2 &lhs, const Vector2 &rhs);
__forceinline void operator *= (Vector2 &lhs, const Vector2 &rhs);
__forceinline void operator += (Vector2 &lhs, const Vector2 &rhs);
__forceinline void operator -= (Vector2 &lhs, const Vector2 &rhs);
__forceinline Vector2 operator - (const Vector2 &v);
__forceinline Vector2 operator + (const Vector2 &v);

__forceinline Vector2 operator / (const Vector2 &lhs, float rhs);
__forceinline Vector2 operator * (const Vector2 &lhs, float rhs);
__forceinline Vector2 operator * (float lhs, const Vector2 &rhs);
__forceinline Vector2 operator + (const Vector2 &lhs, float rhs);
__forceinline Vector2 operator - (const Vector2 &lhs, float rhs);
__forceinline void operator /= (Vector2 &lhs, float rhs);
__forceinline void operator *= (Vector2 &lhs, float rhs);
__forceinline void operator += (Vector2 &lhs, float rhs);
__forceinline void operator -= (Vector2 &lhs, float rhs);

__forceinline bool operator==(const Vector2 &lhs, const Vector2 &rhs);
__forceinline bool operator!=(const Vector2 &lhs, const Vector2 &rhs);

// Methods
__forceinline Vector2 vector2(float x, float y);
__forceinline float & element(Vector2 &m, int i);
__forceinline const float & element(const Vector2 &m, int i);

__forceinline bool is_zero(const Vector2 &v);
__forceinline bool is_zero(const Vector2 &v, float eps);
__forceinline void zero(Vector2 &v);
__forceinline float length(const Vector2 &v);
__forceinline float length_squared(const Vector2 &v);
__forceinline Vector2 normalize(const Vector2 &v);
__forceinline float dot(const Vector2 &v0, const Vector2 &v1);
__forceinline float distance(const Vector2 &v0, const Vector2 &v1);
__forceinline float distance_squared(const Vector2 &v0, const Vector2 &v1);
__forceinline Vector2 lerp(const Vector2 &a, const Vector2 &b, float t);
__forceinline Vector2 min(const Vector2 &v0, const Vector2 &v1);
__forceinline Vector2 max(const Vector2 &v0, const Vector2 &v1);

}

#include "vector2.inl"
