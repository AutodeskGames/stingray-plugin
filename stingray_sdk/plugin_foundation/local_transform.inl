#include "vector3.h"
#include "quaternion.h"

namespace stingray_plugin_foundation {

// ----------------------------------------------------------------------
// Matrix3x3
// ----------------------------------------------------------------------

inline Matrix3x3 matrix3x3_identity()
{
	Matrix3x3 m;
	set_to_identity(m);
	return m;
}

inline void set_to_identity(Matrix3x3 &m)
{
	m.x = vector3(1,0,0);
	m.y = vector3(0,1,0);
	m.z = vector3(0,0,1);
}

inline Matrix3x3 operator*(const Matrix3x3 &a, const Matrix3x3 &b)
{
	Matrix3x3 m;

	m.x.x = a.x.x*b.x.x + a.x.y*b.y.x + a.x.z*b.z.x;
	m.x.y = a.x.x*b.x.y + a.x.y*b.y.y + a.x.z*b.z.y;
	m.x.z = a.x.x*b.x.z + a.x.y*b.y.z + a.x.z*b.z.z;

	m.y.x = a.y.x*b.x.x + a.y.y*b.y.x + a.y.z*b.z.x;
	m.y.y = a.y.x*b.x.y + a.y.y*b.y.y + a.y.z*b.z.y;
	m.y.z = a.y.x*b.x.z + a.y.y*b.y.z + a.y.z*b.z.z;

	m.z.x = a.z.x*b.x.x + a.z.y*b.y.x + a.z.z*b.z.x;
	m.z.y = a.z.x*b.x.y + a.z.y*b.y.y + a.z.z*b.z.y;
	m.z.z = a.z.x*b.x.z + a.z.y*b.y.z + a.z.z*b.z.z;

	return m;
}

inline Matrix3x3 matrix3x3(const Quaternion &q)
{
	const float	d = dot(q,q);
	float s = d ? 2.0f / d : 1.0f;
	const float	xs = q.x * s;
	const float	ys = q.y * s;
	const float	zs = q.z * s;
	const float wx = q.w * xs;
	const float wy = q.w * ys;
	const float wz = q.w * zs;
	const float xx = q.x * xs;
	const float xy = q.x * ys;
	const float xz = q.x * zs;
	const float yy = q.y * ys;
	const float yz = q.y * zs;
	const float zz = q.z * zs;

	Matrix3x3 m;
	m.x = vector3((1.0f - yy - zz), (xy + wz), (xz - wy));
	m.y = vector3((xy - wz), (1.0f - xx - zz), (yz + wx));
	m.z = vector3((xz + wy), (yz - wx), (1.0f - xx - yy));
	return m;
}

inline Matrix3x3 matrix3x3(const Matrix4x4 &tm)
{
	Matrix3x3 m;
	m.x = x_axis(tm);
	m.y = y_axis(tm);
	m.z = z_axis(tm);
	return m;
}

// ----------------------------------------------------------------------
// LocalTransform
// ----------------------------------------------------------------------

inline LocalTransform local_transform(const Matrix3x3 &rot, const Vector3 &pos)
{
	LocalTransform tm;
	tm.rot = rot;
	tm.pos = pos;
	tm.scale = vector3(1,1,1);
	tm.dummy = 0.0f;
	return tm;
}

inline LocalTransform local_transform(const Matrix3x3 &rot, const Vector3 &pos, const Vector3 &scale)
{
	LocalTransform tm;
	tm.rot = rot;
	tm.pos = pos;
	tm.scale = scale;
	tm.dummy = 0.0f;
	return tm;
}

inline LocalTransform local_transform_identity()
{
	LocalTransform tm;
	set_to_identity(tm);
	return tm;
}

inline void set_to_identity(LocalTransform &tm)
{
	set_to_identity(tm.rot);
	tm.pos = vector3(0,0,0);
	tm.scale = vector3(1,1,1);
	tm.dummy = 0.0f;
}

inline Vector3 transform(const LocalTransform &tm, const Vector3 &p)
{
	return tm.pos + p.x*tm.rot.x*tm.scale.x + p.y*tm.rot.y*tm.scale.y + p.z*tm.rot.z*tm.scale.z;
}

inline Vector3 transform_without_translation(const LocalTransform &tm, const Vector3 &p)
{
	return p.x*tm.rot.x*tm.scale.x + p.y*tm.rot.y*tm.scale.y + p.z*tm.rot.z*tm.scale.z;
}

inline LocalTransform operator*(const LocalTransform &a, const LocalTransform &b)
{
	Matrix3x3 a_rs = a.rot;
	Matrix3x3 b_rs = b.rot;

	a_rs.x = a_rs.x * a.scale.x;
	a_rs.y = a_rs.y * a.scale.y;
	a_rs.z = a_rs.z * a.scale.z;

	b_rs.x = b_rs.x * b.scale.x;
	b_rs.y = b_rs.y * b.scale.y;
	b_rs.z = b_rs.z * b.scale.z;

	LocalTransform res;
	res.rot = a_rs * b_rs;
	res.scale = vector3(length(res.rot.x), length(res.rot.y), length(res.rot.z));
	res.rot.x /= res.scale.x; res.rot.y /= res.scale.y; res.rot.z /= res.scale.z;
	res.pos = transform(b, a.pos);
	return res;
}

inline void operator*=(LocalTransform &a, const LocalTransform &b)
{
	a = a*b;
}

inline LocalTransform relative(LocalTransform &child, const LocalTransform &parent)
{
	Matrix4x4 p4i = inverse(matrix4x4(parent));
	Matrix4x4 rm = matrix4x4(child) * p4i;
	return local_transform(rm);
}

inline LocalTransform local_transform(const Matrix4x4 &m4)
{
	LocalTransform tm;
	tm.rot.x = x_axis(m4);
	tm.rot.y = y_axis(m4);
	tm.rot.z = z_axis(m4);

	tm.scale = vector3( length(tm.rot.x), length(tm.rot.y), length(tm.rot.z) );
	if (tm.scale.x && tm.scale.y && tm.scale.z) {
		tm.rot.x /= tm.scale.x;
		tm.rot.y /= tm.scale.y;
		tm.rot.z /= tm.scale.z;
	} else
		tm.rot = matrix3x3_identity();

	tm.pos = translation(m4);
	tm.dummy = 0.0f;

	return tm;
}

inline Matrix4x4 matrix4x4(const LocalTransform &tm)
{
	Matrix4x4 m4 = matrix4x4_identity();
	x_axis(m4) = tm.rot.x * tm.scale.x;
	y_axis(m4) = tm.rot.y * tm.scale.y;
	z_axis(m4) = tm.rot.z * tm.scale.z;
	translation(m4) = tm.pos;
	return m4;
}

}
