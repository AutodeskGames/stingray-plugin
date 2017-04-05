#pragma once

#include "platform.h"
#include "types.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Vector4 operator / (const Vector4 &lhs, const Vector4 &rhs);
__forceinline Vector4 operator * (const Vector4 &lhs, const Vector4 &rhs);
__forceinline Vector4 operator + (const Vector4 &lhs, const Vector4 &rhs);
__forceinline Vector4 operator - (const Vector4 &lhs, const Vector4 &rhs);
__forceinline void operator /= (Vector4 &lhs, const Vector4 &rhs);
__forceinline void operator *= (Vector4 &lhs, const Vector4 &rhs);
__forceinline void operator += (Vector4 &lhs, const Vector4 &rhs);
__forceinline void operator -= (Vector4 &lhs, const Vector4 &rhs);
__forceinline Vector4 operator - (const Vector4 &v);
__forceinline Vector4 operator + (const Vector4 &v);

__forceinline Vector4 operator / (const Vector4 &lhs, float rhs);
__forceinline Vector4 operator * (const Vector4 &lhs, float rhs);
__forceinline Vector4 operator * (float lhs, const Vector4 &rhs);
__forceinline Vector4 operator + (const Vector4 &lhs, float rhs);
__forceinline Vector4 operator - (const Vector4 &lhs, float rhs);
__forceinline void operator /= (Vector4 &lhs, float rhs);
__forceinline void operator *= (Vector4 &lhs, float rhs);
__forceinline void operator += (Vector4 &lhs, float rhs);
__forceinline void operator -= (Vector4 &lhs, float rhs);

__forceinline bool operator==(const Vector4 &lhs, const Vector4 &rhs);
__forceinline bool operator!=(const Vector4 &lhs, const Vector4 &rhs);

// Methods
__forceinline Vector4 vector4(float x, float y, float z, float w);
__forceinline Vector4 vector4_base(int i);
__forceinline float & element(Vector4 &m, int i);
__forceinline const float & element(const Vector4 &m, int i);

__forceinline void zero(Vector4 &v);
__forceinline float length(const Vector4 &v);
__forceinline float norm(const Vector4 &v);
__forceinline float one_norm(const Vector4 &v);
__forceinline float infinity_norm(const Vector4 &v);
__forceinline Vector4 normalize(const Vector4 &v);
__forceinline float dot(const Vector4 &v0, const Vector4 &v1);
__forceinline float distance(const Vector4 &v0, const Vector4 &v1);
__forceinline float distance_squared(const Vector4 &v0, const Vector4 &v1);
__forceinline Vector4 normal_vector(const Vector4 &v0,const Vector4 &v1, const Vector4& v2);
__forceinline Vector4 min(const Vector4 &v0, const Vector4 &v1);
__forceinline Vector4 max(const Vector4 &v0, const Vector4 &v1);

__forceinline Vector4 lerp(const Vector4 &a, const Vector4 &b, float t);

__forceinline Vector3 vector3(const Vector4 &a);

}

#include "vector4.inl"
