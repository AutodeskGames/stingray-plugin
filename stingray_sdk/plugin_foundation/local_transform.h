#pragma once

#include "types.h"

namespace stingray_plugin_foundation {

// ----------------------------------------------------------------------
// Matrix3x3
// ----------------------------------------------------------------------

// Constructors
inline Matrix3x3 matrix3x3_identity();

// Operations
inline void set_to_identity(Matrix3x3 &tm);
inline Matrix3x3 operator*(const Matrix3x3 &a, const Matrix3x3 &b);

// Conversions
inline Matrix3x3 matrix3x3(const Quaternion &q);
inline Matrix3x3 matrix3x3(const Matrix4x4 &m);

// ----------------------------------------------------------------------
// LocalTransform
// ----------------------------------------------------------------------

// Constructors
inline LocalTransform local_transform(const Matrix3x3 &rot, const Vector3 &pos);
inline LocalTransform local_transform(const Matrix3x3 &rot, const Vector3 &pos, const Vector3 &scale);
inline LocalTransform local_transform_identity();

// Operations
inline void set_to_identity(LocalTransform &tm);
inline LocalTransform operator*(const LocalTransform &a, const LocalTransform &b);
inline void operator*=(LocalTransform &a, const LocalTransform &b);
inline LocalTransform relative(LocalTransform &child, const LocalTransform &parent);

// Conversions
inline LocalTransform local_transform(const Matrix4x4 &tm);
inline Matrix4x4 matrix4x4(const LocalTransform &tm);

// Utility
inline Vector3 transform(const LocalTransform &tm, const Vector3 &p);
inline Vector3 transform_without_translation(const LocalTransform &tm, const Vector3 &p);

}

#include "local_transform.inl"
