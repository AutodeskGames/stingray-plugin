#pragma once

#include "platform.h"
#include "types.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Quaternion operator +(const Quaternion &q);
__forceinline Quaternion operator -(const Quaternion &q);
__forceinline Quaternion operator +(const Quaternion &lhs, const Quaternion &rhs);
__forceinline Quaternion operator -(const Quaternion &lhs, const Quaternion &rhs);
__forceinline Quaternion operator *(const Quaternion &lhs, const Quaternion &rhs);
__forceinline Quaternion operator *(const Quaternion &lhs, float rhs);
__forceinline Quaternion operator *(float lhs, const Quaternion &rhs);
__forceinline Quaternion operator /(const Quaternion &lhs, float rhs);

__forceinline void operator +=(Quaternion &lhs, const Quaternion &rhs);
__forceinline void operator -=(Quaternion &lhs, const Quaternion &rhs);
__forceinline void operator *=(Quaternion &lhs, const Quaternion &rhs);
__forceinline void operator *=(Quaternion &lhs, float rhs);

__forceinline bool operator==(const Quaternion &lhs, const Quaternion &rhs);
__forceinline bool operator!=(const Quaternion &lhs, const Quaternion &rhs);
__forceinline bool operator< (const Quaternion &lhs, const Quaternion &rhs);
__forceinline bool operator<=(const Quaternion &lhs, const Quaternion &rhs);
__forceinline bool operator> (const Quaternion &lhs, const Quaternion &rhs);
__forceinline bool operator>=(const Quaternion &lhs, const Quaternion &rhs);

// Creation Methods
__forceinline Quaternion quaternion(const float * list);
__forceinline Quaternion quaternion(float x, float y, float z, float w);
__forceinline const Quaternion &quaternion_identity();
__forceinline Quaternion quaternion(const Vector3 &axis, float theta);
Quaternion quaternion(const Vector3 &forward, const Vector3 &up);
Quaternion quaternion(const Matrix4x4 &m);
Quaternion quaternion(const Matrix3x3 &m);
Quaternion quaternion_orthogonal(const Matrix4x4 &m);

// Methods
__forceinline Quaternion normalize(const Quaternion &q);
__forceinline Quaternion inverse(const Quaternion &q);
__forceinline Quaternion conjugate(const Quaternion &q);
__forceinline float dot(const Quaternion &q1, const Quaternion &q2);
__forceinline Quaternion slerp(const Quaternion &from, const Quaternion &to, float t);
__forceinline Quaternion nlerp(const Quaternion &from, const Quaternion &to, float t);
__forceinline Quaternion lerp(const Quaternion &from, const Quaternion &to, float t);
__forceinline Quaternion scale_angle(const Quaternion &from, float t);

__forceinline bool is_zero(const Quaternion &q);
__forceinline float norm(const Quaternion &q);
__forceinline float one_norm(const Quaternion &q);
__forceinline float infinity_norm(const Quaternion &q);

// Rotate Vector3 with quaternion.
__forceinline Vector3 rotate(const Quaternion &q, const Vector3 &v);

// Conversion Methods
__forceinline Matrix4x4 matrix4x4(const Quaternion &q);
__forceinline Matrix4x4 matrix4x4(const Quaternion &q, const Vector3 &p);
__forceinline void decompose(const Quaternion &q, Vector3 *axis, float *theta);
__forceinline float angle(const Quaternion &q);

// Lerps the matrix by lerping Quaternion and Vector3 separately.
__forceinline void lerp(const Matrix4x4 &m1, const Matrix4x4 &m2, float t, Matrix4x4 &m);

}

#include "quaternion.inl"
