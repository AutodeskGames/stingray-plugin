#pragma once

#include "types.h"
#include "platform.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Matrix4x4	operator *(const Matrix4x4& lhs, const Matrix4x4 &rhs);
__forceinline Matrix4x4	operator +(const Matrix4x4& lhs, const Matrix4x4 &rhs);
__forceinline Matrix4x4	operator -(const Matrix4x4& lhs, const Matrix4x4 &rhs);

__forceinline void operator *=(Matrix4x4& lhs, const Matrix4x4 &rhs);
__forceinline void operator +=(Matrix4x4& lhs, const Matrix4x4 &rhs);
__forceinline void operator -=(Matrix4x4& lhs, const Matrix4x4 &rhs);

__forceinline bool operator==(const Matrix4x4 &lhs, const Matrix4x4 &rhs);
__forceinline bool operator!=(const Matrix4x4 &lhs, const Matrix4x4 &rhs);

__forceinline Matrix4x4	operator *(const Matrix4x4& lhs, float rhs);
__forceinline Matrix4x4	operator *(float lhs, const Matrix4x4 &rhs);

// Methods
__forceinline void set_to_zero_matrix(Matrix4x4 &m);
__forceinline void set_to_identity_matrix(Matrix4x4 &m);
__forceinline void set_to_scale_matrix(Matrix4x4 &m, const Vector3 &s);
__forceinline void set_to_translation_matrix(Matrix4x4 &m, const Vector3 &t);
__forceinline const Matrix4x4 &matrix4x4_zero();
__forceinline const Matrix4x4 &matrix4x4_identity();
__forceinline void normalize(Matrix4x4 &m);
__forceinline float determinant(const Matrix4x4 &m);
__forceinline bool has_mirroring(const Matrix4x4 &m);

Matrix4x4 inverse(const Matrix4x4 &m);

__forceinline float & element(Matrix4x4 &m, int i, int j);
__forceinline const float & element(const Matrix4x4 &m, int i, int j);

__forceinline void transpose(Matrix4x4 &m);

__forceinline Matrix4x4 rotation(const Matrix4x4 &m);
__forceinline void set_rotation(Matrix4x4 &m, const Matrix4x4 &rot);

__forceinline Vector3 scale(const Matrix4x4 &m);
__forceinline void set_scale(Matrix4x4 &m, const Vector3 &scale);

// Vector3 helper access
__forceinline Vector3 &translation(Matrix4x4 &m);
__forceinline Vector3 &x_axis(Matrix4x4 &m);
__forceinline Vector3 &y_axis(Matrix4x4 &m);
__forceinline Vector3 &z_axis(Matrix4x4 &m);
__forceinline const Vector3 &translation(const Matrix4x4 &m);
__forceinline const Vector3 &x_axis(const Matrix4x4 &m);
__forceinline const Vector3 &y_axis(const Matrix4x4 &m);
__forceinline const Vector3 &z_axis(const Matrix4x4 &m);

__forceinline void set_translation(Matrix4x4 &m, const Vector3 &t);

__forceinline Vector3 &forward_axis(Matrix4x4 &m);
__forceinline Vector3 &up_axis(Matrix4x4 &m);
__forceinline Vector3 &right_axis(Matrix4x4 &m);
__forceinline const Vector3 &forward_axis(const Matrix4x4 &m);
__forceinline const Vector3 &up_axis(const Matrix4x4 &m);
__forceinline const Vector3 &right_axis(const Matrix4x4 &m);

__forceinline Vector3 &axis(Matrix4x4 &m, int i);
__forceinline const Vector3 &axis(const Matrix4x4 &m, int i);
__forceinline Vector4 &row(Matrix4x4 &m, int i);
__forceinline const Vector4 &row(const Matrix4x4 &m, int i);

// Transforms the point p with the matrix m.
__forceinline Vector3 transform(const Matrix4x4 &m, const Vector3 &p);
__forceinline Vector3 transform_without_translation(const Matrix4x4 &m, const Vector3 &p);
__forceinline Vector4 transform(const Matrix4x4 &m, const Vector4 &p);

}

#include "matrix4x4.inl"
