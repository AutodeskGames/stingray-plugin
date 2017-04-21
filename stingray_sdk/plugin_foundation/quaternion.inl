#include "vector3.h"
#include "matrix4x4.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Quaternion operator +(const Quaternion &q) {
	return q;
}

__forceinline Quaternion operator -(const Quaternion &q) {
	return quaternion(-q.x, -q.y, -q.z, q.w);
}

__forceinline Quaternion operator +(const Quaternion &lhs, const Quaternion &rhs) {
	return quaternion(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z, lhs.w+rhs.w);
}

__forceinline Quaternion operator -(const Quaternion &lhs, const Quaternion &rhs) {
	return quaternion(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z, lhs.w-rhs.w);
}

__forceinline Quaternion operator *(const Quaternion &lhs, const Quaternion &rhs) {
	return quaternion(
		lhs.w*rhs.x + lhs.x*rhs.w + lhs.y*rhs.z - lhs.z*rhs.y,
		lhs.w*rhs.y + lhs.y*rhs.w + lhs.z*rhs.x - lhs.x*rhs.z,
		lhs.w*rhs.z + lhs.z*rhs.w + lhs.x*rhs.y - lhs.y*rhs.x,
		lhs.w*rhs.w - lhs.x*rhs.x - lhs.y*rhs.y - lhs.z*rhs.z
	);
}

__forceinline Quaternion operator *(const Quaternion &lhs, float rhs) {
	return quaternion(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs, lhs.w*rhs);
}

__forceinline Quaternion operator *(float lhs, const Quaternion &rhs) {
	return rhs * lhs;
}

__forceinline Quaternion operator /(const Quaternion &lhs, float rhs) {
	return quaternion(lhs.x/rhs, lhs.y/rhs, lhs.z/rhs, lhs.w/rhs);
}

__forceinline void operator +=(Quaternion &lhs, const Quaternion &rhs) {
	lhs.x+=rhs.x; lhs.y+=rhs.y;	lhs.z+=rhs.z; lhs.w+=rhs.w;
}

__forceinline void operator -=(Quaternion &lhs, const Quaternion &rhs) {
	lhs.x-=rhs.x; lhs.y-=rhs.y; lhs.z-=rhs.z; lhs.w-=rhs.w;
}

__forceinline void operator *=(Quaternion &lhs, const Quaternion &rhs) {
	lhs.x*=rhs.x; lhs.y*=rhs.y;	lhs.z*=rhs.z; lhs.w*=rhs.w;

}

__forceinline void operator *=(Quaternion &lhs, float rhs) {
	lhs.x*=rhs; lhs.y*=rhs;	lhs.z*=rhs; lhs.w*=rhs;
}

__forceinline bool operator==(const Quaternion &lhs, const Quaternion &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

__forceinline bool operator!=(const Quaternion &lhs, const Quaternion &rhs)
{
	return !(lhs == rhs);
}

__forceinline bool operator< (const Quaternion &lhs, const Quaternion &rhs)
{
	if (lhs.x != rhs.x) return lhs.x < rhs.x;
	if (lhs.y != rhs.y) return lhs.y < rhs.y;
	if (lhs.z != rhs.z) return lhs.z < rhs.z;
	return lhs.w < rhs.w;
}

__forceinline bool operator<=(const Quaternion &lhs, const Quaternion &rhs)
{
	return (lhs < rhs) || (lhs == rhs);
}

__forceinline bool operator> (const Quaternion &lhs, const Quaternion &rhs)
{
	return (rhs < lhs);
}

__forceinline bool operator>=(const Quaternion &lhs, const Quaternion &rhs)
{
	return !(lhs < rhs);
}

// Creation Methods

__forceinline Quaternion quaternion(const float * list) {
	Quaternion q = { *list, *(list+1), *(list+2), *(list+3) };
	return q;
}

__forceinline Quaternion quaternion(float x, float y, float z, float w) {
	Quaternion q = { x, y, z, w };
	return q;
}

__forceinline const Quaternion &quaternion_identity() {
	static Quaternion q = { 0.f, 0.f, 0.f, 1.f };
	return q;
}

__forceinline Quaternion quaternion(const Vector3 &axis, float theta) {
	Quaternion q;

	float halftheta = theta * 0.5f;
	float cos_ht = cosf( halftheta );
	float sin_ht = sinf( halftheta );

	q.x = axis.x * sin_ht;
	q.y = axis.y * sin_ht;
	q.z = axis.z * sin_ht;
	q.w = cos_ht;

	return q;
}

// Methods
__forceinline Quaternion normalize(const Quaternion &q) {
	float l = math::square_root( dot(q,q) );

	if(l == 0.0f)
		return quaternion(0.f, 0.f, 0.f, 1.f);
	else {
		float c = 1.0f / l;
		return quaternion(q.x*c, q.y*c, q.z*c, q.w*c);
	}
}

__forceinline Quaternion inverse(const Quaternion &q) {
	float l = dot(q,q);
	if (l == 0.0f)
		l = 1.0f;
	float norminv = -1.0f / l;
	return quaternion(q.x*norminv, q.y*norminv, q.z*norminv, q.w*-norminv);
}

__forceinline Quaternion conjugate(const Quaternion &q) {
	return quaternion(-q.x, -q.y, -q.z, q.w);
}

__forceinline float dot(const Quaternion &q1, const Quaternion &q2) {
	return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
}

__forceinline Quaternion slerp(const Quaternion &from, const Quaternion &to, float t) {
	Quaternion q;
	Quaternion q3;

	float d = dot(from, to);
	if (d < 0) {
		d = -d;
		q3 = to * -1.0f;
	} else
		q3 = to;

	// Use linear interpolation for small angles.
	if (d < 0.95f) {
		float clamped_dot = math::clamp(d, -1.0f, 1.0f);
		float angle = acosf(clamped_dot);
		float sina, sinat, sinaomt;
		sina = sinf(angle);
		sinat = sinf(angle*t);
		sinaomt = sinf(angle*(1-t));
		q = (from*sinaomt+q3*sinat)/sina;
	} else
		q = nlerp(from, q3,t);

	return q;

}

__forceinline Quaternion nlerp(const Quaternion &from, const Quaternion &to, float t) {
	Quaternion q;
	if(dot(from, to) < 0)
		q = ((to + from) * t) - from;
	else
		q = from + ((to - from) * t);
	return normalize(q);
}

// lerp for quaternions defaults to nlerp
__forceinline Quaternion lerp(const Quaternion &from, const Quaternion &to, float t) {
	Quaternion q;
	if(dot(from, to) < 0)
		q = ((to + from) * t) - from;
	else
		q = from + ((to - from) * t);
	return normalize(q);
}

// Scales the angle in the rotation the quaternion represents by t.
__forceinline Quaternion scale_angle(const Quaternion &from, float t)
{
	Vector3 axis;
	float theta;
	decompose(from, &axis, &theta);
	return quaternion(axis, theta*t);
}

__forceinline bool is_zero(const Quaternion &q)
{
	return q.x == 0 && q.y == 0 && q.z == 0 && q.w == 0;
}

__forceinline float norm(const Quaternion &q)
{
	return math::square_root(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
}

__forceinline float one_norm(const Quaternion &q)
{
	return math::abs(q.x) + math::abs(q.y) + math::abs(q.z) + math::abs(q.w);
}

__forceinline float infinity_norm(const Quaternion &q)
{
	return math::max<float>(
		math::max<float>(math::abs(q.x),
		math::abs(q.y)),
		math::max<float>(math::abs(q.z),
		math::abs(q.w)) );
}

__forceinline Vector3 rotate(const Quaternion &q, const Vector3 &v)
{
	Quaternion v_quat = quaternion(v.x, v.y, v.z, 0.0f);
	Quaternion result(q * v_quat * conjugate(q));
	return vector3(result.x, result.y, result.z);
}

// Conversion Methods
__forceinline Matrix4x4 matrix4x4(const Quaternion &q) {
	const float	d = dot(q,q);
	float s;
	if(d)
		s = 2.0f / d;
	else
		s = 1.0f;

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

	Matrix4x4 m = {
		(1.0f - yy - zz), (xy + wz), (xz - wy), 0.0f,
		(xy - wz), (1.0f - xx - zz), (yz + wx), 0.0f,
		(xz + wy), (yz - wx), (1.0f - xx - yy), 0.0f,
		0.f, 0.f, 0.f, 1.f
	};

	return m;
}

__forceinline Matrix4x4 matrix4x4(const Quaternion &q, const Vector3 &p)
{
	const float	d = dot(q,q);
	float s;
	if(d)
		s = 2.0f / d;
	else
		s = 1.0f;

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

	Matrix4x4 m = {
		(1.0f - yy - zz), (xy + wz), (xz - wy), 0.0f,
		(xy - wz), (1.0f - xx - zz), (yz + wx), 0.0f,
		(xz + wy), (yz - wx), (1.0f - xx - yy), 0.0f,
		p.x, p.y, p.z, 1.f
	};

	return m;
}

__forceinline void decompose(const Quaternion &q, Vector3 *axis, float *theta)
{
	Vector3 a = vector3(q.x, q.y, q.z);
	float s = length(a);
	float c = q.w;
	float half_theta = atan2f(s, c);
	*theta = half_theta * 2.0f;
	*axis = s ? a / s : vector3(1,0,0);
}

__forceinline float angle(const Quaternion &q)
{
	Vector3 a = vector3(q.x, q.y, q.z);
	float s = length(a);
	float c = q.w;
	float half_theta = atan2f(s, c);
	return half_theta * 2.0f;
}

__forceinline void lerp(const Matrix4x4 &m1, const Matrix4x4 &m2, float t, Matrix4x4 &m)
{
	Vector3 p = lerp(translation(m1), translation(m2), t);
	Quaternion q = lerp(quaternion(m1), quaternion(m2), t);
	m = matrix4x4(q, p);
}

inline Quaternion quaternion_orthogonal(const Matrix4x4 &mat) {
	static const int kx = 0;
	static const int ky = 1;
	static const int kz = 2;
	static const int kw = 3;

	struct ShadowMatrix	{
		float m[4][4];
	};
	const ShadowMatrix* m = reinterpret_cast<const ShadowMatrix*>(&mat);
	Quaternion r;
	float *q = reinterpret_cast<float *>(&r);

	// This code can be optimized for m[kw][kw] = 1, which
	// should always be true.  This optimization is excluded
	// here for clarity.
	float trace = m->m[kx][kx] + m->m[ky][ky] + m->m[kz][kz] + m->m[kw][kw];
	float four_d;
	int i,j,k;

	if (trace >= 1.0) // w >= 0.5
	{
		four_d = 2.0f*math::square_root(trace);
		q[kw] = -four_d / 4.0f;
		const float one_over_coeff = 1.0f / four_d;
		q[kx] = (m->m[kz][ky] - m->m[ky][kz])*one_over_coeff;
		q[ky] = (m->m[kx][kz] - m->m[kz][kx])*one_over_coeff;
		q[kz] = (m->m[ky][kx] - m->m[kx][ky])*one_over_coeff;
	}
	else
	{
		// Find the largest component
		if (m->m[kx][kx] > m->m[ky][ky])
			i = kx;
		else
			i = ky;
		if (m->m[kz][kz] > m->m[i][i])
			i = kz;

		// Set j and k to next two components
		j = (1 << i) & 3;
		k = (1 << j) & 3;

		four_d = 2.0f*math::square_root(m->m[i][i] - m->m[j][j] - m->m[k][k] + 1.0f );
		q[i] = four_d/4.0f;

		const float one_over_coeff = 1.0f / four_d;
		q[j] = (m->m[j][i] + m->m[i][j])*one_over_coeff;
		q[k] = (m->m[k][i] + m->m[i][k])*one_over_coeff;
		q[kw] = -(m->m[k][j] - m->m[j][k])*one_over_coeff;
	}

	return r;
}

inline Quaternion quaternion(const Matrix4x4 &mat)
{
	static const int kx = 0;
	static const int ky = 1;
	static const int kz = 2;
	static const int kw = 3;

	const Vector3 scale = stingray_plugin_foundation::scale(mat);
	const float *s = reinterpret_cast<const float *>(&scale);

	// If scale is small return an identity quaternion
	const float eps = 1e-5;
	if (scale.x > -eps && scale.x < eps || scale.y > -eps && scale.y < eps || scale.z > -eps && scale.z < eps)
		return quaternion_identity();

	struct ShadowMatrix	{
		float m[4][4];
	};
	const ShadowMatrix* m = reinterpret_cast<const ShadowMatrix*>(&mat);
	Quaternion r;
	float *q = reinterpret_cast<float *>(&r);

	// This code can be optimized for m[kw][kw] = 1, which
	// should always be true.  This optimization is excluded
	// here for clarity.
	const float trace = m->m[kx][kx] / s[kx] + m->m[ky][ky] / s[ky] + m->m[kz][kz] / s[kz] + m->m[kw][kw];

	if (trace >= 1.0) // w >= 0.5
	{
		const float four_d = 2.0f*math::square_root(trace);
		q[kw] = -four_d / 4.0f;
		const float one_over_coeff = 1.0f / four_d;
		q[kx] = (m->m[kz][ky] / s[kz] - m->m[ky][kz] / s[ky])*one_over_coeff;
		q[ky] = (m->m[kx][kz] / s[kx] - m->m[kz][kx] / s[kz])*one_over_coeff;
		q[kz] = (m->m[ky][kx] / s[ky] - m->m[kx][ky] / s[kx])*one_over_coeff;
	}
	else
	{
		// Find the largest component
		int i;
		if (m->m[kx][kx] / s[kx] > m->m[ky][ky] / s[ky])
			i = kx;
		else
			i = ky;
		if (m->m[kz][kz] / s[kz] > m->m[i][i] / s[i])
			i = kz;

		// Set j and k to next two components
		const int j = (1 << i) & 3;
		const int k = (1 << j) & 3;

		const float four_d = 2.0f*math::square_root(m->m[i][i] / s[i] - m->m[j][j] / s[j] - m->m[k][k] / s[k] + 1.0f );
		q[i] = four_d/4.0f;

		const float one_over_coeff = 1.0f / four_d;
		q[j] = (m->m[j][i] / s[j] + m->m[i][j] / s[i])*one_over_coeff;
		q[k] = (m->m[k][i] / s[k] + m->m[i][k] / s[i])*one_over_coeff;
		q[kw] = -(m->m[k][j] / s[k] - m->m[j][k] / s[j])*one_over_coeff;
	}

	return r;
}

inline Quaternion quaternion(const Matrix3x3 &mat)
{
	static const int kx = 0;
	static const int ky = 1;
	static const int kz = 2;
	static const int kw = 3;

	struct ShadowMatrix	{
		float m[3][3];
	};
	const ShadowMatrix* m = reinterpret_cast<const ShadowMatrix*>(&mat);
	Quaternion r;
	float *q = reinterpret_cast<float *>(&r);

	float trace = m->m[kx][kx] + m->m[ky][ky] + m->m[kz][kz] + 1;
	float four_d;
	int i,j,k;

	if (trace >= 1.0) // w >= 0.5
	{
		four_d = 2.0f*math::square_root(trace);
		q[kw] = -four_d / 4.0f;
		const float one_over_coeff = 1.0f / four_d;
		q[kx] = (m->m[kz][ky] - m->m[ky][kz])*one_over_coeff;
		q[ky] = (m->m[kx][kz] - m->m[kz][kx])*one_over_coeff;
		q[kz] = (m->m[ky][kx] - m->m[kx][ky])*one_over_coeff;
	}
	else
	{
		// Find the largest component
		if (m->m[kx][kx] > m->m[ky][ky])
			i = kx;
		else
			i = ky;
		if (m->m[kz][kz] > m->m[i][i])
			i = kz;

		// Set j and k to next two components
		j = (1 << i) & 3;
		k = (1 << j) & 3;

		four_d = 2.0f*math::square_root(m->m[i][i] - m->m[j][j] - m->m[k][k] + 1.0f );
		q[i] = four_d/4.0f;

		const float one_over_coeff = 1.0f / four_d;
		q[j] = (m->m[j][i] + m->m[i][j])*one_over_coeff;
		q[k] = (m->m[k][i] + m->m[i][k])*one_over_coeff;
		q[kw] = -(m->m[k][j] - m->m[j][k])*one_over_coeff;
	}

	return r;
}

inline Quaternion quaternion(const Vector3 &y, const Vector3 &z)
{
	Vector3 x = cross(y,z);
	Matrix4x4 tm = matrix4x4_identity();
	x_axis(tm) = x;
	y_axis(tm) = y;
	z_axis(tm) = z;
	return quaternion_orthogonal(tm);
}

}
