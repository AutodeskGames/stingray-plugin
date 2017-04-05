#include "vector3.h"

namespace stingray_plugin_foundation {

enum Elements {
	xx, xy, xz, xw,
	yx, yy, yz, yw,
	zx, zy, zz, zw,
	tx, ty, tz, tw
};

// Operators

__forceinline Matrix4x4	operator *(const Matrix4x4& lhs, const Matrix4x4 &rhs) {
	Matrix4x4 m = {{
		lhs.v[xx]*rhs.v[xx] + lhs.v[xy]*rhs.v[yx] + lhs.v[xz]*rhs.v[zx] + lhs.v[xw]*rhs.v[tx],
		lhs.v[xx]*rhs.v[xy] + lhs.v[xy]*rhs.v[yy] + lhs.v[xz]*rhs.v[zy] + lhs.v[xw]*rhs.v[ty],
		lhs.v[xx]*rhs.v[xz] + lhs.v[xy]*rhs.v[yz] + lhs.v[xz]*rhs.v[zz] + lhs.v[xw]*rhs.v[tz],
		lhs.v[xx]*rhs.v[xw] + lhs.v[xy]*rhs.v[yw] + lhs.v[xz]*rhs.v[zw] + lhs.v[xw]*rhs.v[tw],
		lhs.v[yx]*rhs.v[xx] + lhs.v[yy]*rhs.v[yx] + lhs.v[yz]*rhs.v[zx] + lhs.v[yw]*rhs.v[tx],
		lhs.v[yx]*rhs.v[xy] + lhs.v[yy]*rhs.v[yy] + lhs.v[yz]*rhs.v[zy] + lhs.v[yw]*rhs.v[ty],
		lhs.v[yx]*rhs.v[xz] + lhs.v[yy]*rhs.v[yz] + lhs.v[yz]*rhs.v[zz] + lhs.v[yw]*rhs.v[tz],
		lhs.v[yx]*rhs.v[xw] + lhs.v[yy]*rhs.v[yw] + lhs.v[yz]*rhs.v[zw] + lhs.v[yw]*rhs.v[tw],
		lhs.v[zx]*rhs.v[xx] + lhs.v[zy]*rhs.v[yx] + lhs.v[zz]*rhs.v[zx] + lhs.v[zw]*rhs.v[tx],
		lhs.v[zx]*rhs.v[xy] + lhs.v[zy]*rhs.v[yy] + lhs.v[zz]*rhs.v[zy] + lhs.v[zw]*rhs.v[ty],
		lhs.v[zx]*rhs.v[xz] + lhs.v[zy]*rhs.v[yz] + lhs.v[zz]*rhs.v[zz] + lhs.v[zw]*rhs.v[tz],
		lhs.v[zx]*rhs.v[xw] + lhs.v[zy]*rhs.v[yw] + lhs.v[zz]*rhs.v[zw] + lhs.v[zw]*rhs.v[tw],
		lhs.v[tx]*rhs.v[xx] + lhs.v[ty]*rhs.v[yx] + lhs.v[tz]*rhs.v[zx] + lhs.v[tw]*rhs.v[tx],
		lhs.v[tx]*rhs.v[xy] + lhs.v[ty]*rhs.v[yy] + lhs.v[tz]*rhs.v[zy] + lhs.v[tw]*rhs.v[ty],
		lhs.v[tx]*rhs.v[xz] + lhs.v[ty]*rhs.v[yz] + lhs.v[tz]*rhs.v[zz] + lhs.v[tw]*rhs.v[tz],
		lhs.v[tx]*rhs.v[xw] + lhs.v[ty]*rhs.v[yw] + lhs.v[tz]*rhs.v[zw] + lhs.v[tw]*rhs.v[tw]
	}};

	return m;
}

__forceinline Matrix4x4	operator +(const Matrix4x4& lhs, const Matrix4x4 &rhs) {
	Matrix4x4 m = {{
		lhs.v[xx] + rhs.v[xx], lhs.v[xy] + rhs.v[xy], lhs.v[xz] + rhs.v[xz], lhs.v[xw] + rhs.v[xw],
		lhs.v[yx] + rhs.v[yx], lhs.v[yy] + rhs.v[yy], lhs.v[yz] + rhs.v[yz], lhs.v[yw] + rhs.v[yw],
		lhs.v[zx] + rhs.v[zx], lhs.v[zy] + rhs.v[zy], lhs.v[zz] + rhs.v[zz], lhs.v[zw] + rhs.v[zw],
		lhs.v[tx] + rhs.v[tx], lhs.v[ty] + rhs.v[ty], lhs.v[tz] + rhs.v[tz], lhs.v[tw] + rhs.v[tw]
	}};
	return m;
}

__forceinline Matrix4x4	operator -(const Matrix4x4& lhs, const Matrix4x4 &rhs) {
	Matrix4x4 m = {{
		lhs.v[xx] - rhs.v[xx], lhs.v[xy] - rhs.v[xy], lhs.v[xz] - rhs.v[xz], lhs.v[xw] - rhs.v[xw],
		lhs.v[yx] - rhs.v[yx], lhs.v[yy] - rhs.v[yy], lhs.v[yz] - rhs.v[yz], lhs.v[yw] - rhs.v[yw],
		lhs.v[zx] - rhs.v[zx], lhs.v[zy] - rhs.v[zy], lhs.v[zz] - rhs.v[zz], lhs.v[zw] - rhs.v[zw],
		lhs.v[tx] - rhs.v[tx], lhs.v[ty] - rhs.v[ty], lhs.v[tz] - rhs.v[tz], lhs.v[tw] - rhs.v[tw]
	}};
	return m;
}

__forceinline void operator *=(Matrix4x4& lhs, const Matrix4x4 &rhs) {
	Matrix4x4 tmp = lhs * rhs;
	lhs = tmp;
}

__forceinline void operator +=(Matrix4x4& lhs, const Matrix4x4 &rhs) {
	lhs.v[xx] += rhs.v[xx]; lhs.v[xy] += rhs.v[xy]; lhs.v[xz] += rhs.v[xz]; lhs.v[xw] += rhs.v[xw];
	lhs.v[yx] += rhs.v[yx]; lhs.v[yy] += rhs.v[yy]; lhs.v[yz] += rhs.v[yz]; lhs.v[yw] += rhs.v[yw];
	lhs.v[zx] += rhs.v[zx]; lhs.v[zy] += rhs.v[zy]; lhs.v[zz] += rhs.v[zz]; lhs.v[zw] += rhs.v[zw];
	lhs.v[tx] += rhs.v[tx]; lhs.v[ty] += rhs.v[ty]; lhs.v[tz] += rhs.v[tz]; lhs.v[tw] += rhs.v[tw];
}

__forceinline void operator -=(Matrix4x4& lhs, const Matrix4x4 &rhs) {
	lhs.v[xx] -= rhs.v[xx]; lhs.v[xy] -= rhs.v[xy]; lhs.v[xz] -= rhs.v[xz]; lhs.v[xw] -= rhs.v[xw];
	lhs.v[yx] -= rhs.v[yx]; lhs.v[yy] += rhs.v[yy]; lhs.v[yz] -= rhs.v[yz]; lhs.v[yw] -= rhs.v[yw];
	lhs.v[zx] -= rhs.v[zx]; lhs.v[zy] += rhs.v[zy]; lhs.v[zz] -= rhs.v[zz]; lhs.v[zw] -= rhs.v[zw];
	lhs.v[tx] -= rhs.v[tx]; lhs.v[ty] -= rhs.v[ty]; lhs.v[tz] -= rhs.v[tz]; lhs.v[tw] -= rhs.v[tw];
}

__forceinline Matrix4x4	operator *(const Matrix4x4& lhs, float rhs) {
	Matrix4x4 m = {{
		lhs.v[xx] * rhs, lhs.v[xy] * rhs, lhs.v[xz] * rhs, lhs.v[xw] * rhs,
		lhs.v[yx] * rhs, lhs.v[yy] * rhs, lhs.v[yz] * rhs, lhs.v[yw] * rhs,
		lhs.v[zx] * rhs, lhs.v[zy] * rhs, lhs.v[zz] * rhs, lhs.v[zw] * rhs,
		lhs.v[tx] * rhs, lhs.v[ty] * rhs, lhs.v[tz] * rhs, lhs.v[tw] * rhs
	}};
	return m;
}

__forceinline Matrix4x4	operator *(float lhs, const Matrix4x4 &rhs) {
	return rhs * lhs;
}

__forceinline bool operator==(const Matrix4x4 &lhs, const Matrix4x4 &rhs)
{
	for (int i=0; i<16; ++i)
		if (lhs.v[i] != rhs.v[i])
			return false;
	return true;
}

__forceinline bool operator!=(const Matrix4x4 &lhs, const Matrix4x4 &rhs)
{
	return !(lhs == rhs);
}

// Methods

__forceinline void set_to_zero_matrix(Matrix4x4 &m)
{
	m.v[xx]=m.v[xy]=m.v[xz]=m.v[xw]=0.f;
	m.v[yx]=m.v[yy]=m.v[yz]=m.v[yw]=0.f;
	m.v[zx]=m.v[zy]=m.v[zz]=m.v[zw]=0.f;
	m.v[tx]=m.v[ty]=m.v[tz]=m.v[tw]=0.f;
}

__forceinline void set_to_identity_matrix(Matrix4x4 &m)
{
	m = matrix4x4_identity();
}

__forceinline const Matrix4x4 &matrix4x4_zero()
{
	static Matrix4x4 zero = {{
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f
	}};
	return zero;
}

__forceinline const Matrix4x4 &matrix4x4_identity()
{
	static Matrix4x4 id = {{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	}};
	return id;
}

__forceinline void set_to_scale_matrix(Matrix4x4 &m, const Vector3 &s)
{
	set_to_identity_matrix(m);
	m.v[xx] = s.x;
	m.v[yy] = s.y;
	m.v[zz] = s.z;
}

__forceinline void set_to_translation_matrix(Matrix4x4 &m, const Vector3 &t)
{
	set_to_identity_matrix(m);
	m.v[tx] = t.x;
	m.v[ty] = t.y;
	m.v[tz] = t.z;
}

__forceinline void normalize(Matrix4x4 &m) {
	Vector3 &x = x_axis(m);
	Vector3 &y = y_axis(m);
	Vector3 &z = z_axis(m);

	x = normalize(x);
	y -= x*dot(x, y);
	y = normalize(y);
	z = cross(x,y);
}

__forceinline float determinant(const Matrix4x4 &m) {
//	return m.v[xx]*m.v[yy]*m.v[zz] + m.v[xy]*m.v[yz]*m.v[zx] + m.v[xz]*m.v[yx]*m.v[zy] -
//		m.v[xz]*m.v[yy]*m.v[zx] - m.v[xy]*m.v[yx]*m.v[zz] - m.v[xx]*m.v[yz]*m.v[zy];

	return
		m.v[3] * m.v[6] * m.v[ 9] * m.v[12] - m.v[2] * m.v[7] * m.v[ 9] * m.v[12] - m.v[3] * m.v[5] * m.v[10] * m.v[12] + m.v[1] * m.v[7] * m.v[10] * m.v[12] +
		m.v[2] * m.v[5] * m.v[11] * m.v[12] - m.v[1] * m.v[6] * m.v[11] * m.v[12] - m.v[3] * m.v[6] * m.v[ 8] * m.v[13] + m.v[2] * m.v[7] * m.v[ 8] * m.v[13] +
		m.v[3] * m.v[4] * m.v[10] * m.v[13] - m.v[0] * m.v[7] * m.v[10] * m.v[13] - m.v[2] * m.v[4] * m.v[11] * m.v[13] + m.v[0] * m.v[6] * m.v[11] * m.v[13] +
		m.v[3] * m.v[5] * m.v[ 8] * m.v[14] - m.v[1] * m.v[7] * m.v[ 8] * m.v[14] - m.v[3] * m.v[4] * m.v[ 9] * m.v[14] + m.v[0] * m.v[7] * m.v[ 9] * m.v[14] +
		m.v[1] * m.v[4] * m.v[11] * m.v[14] - m.v[0] * m.v[5] * m.v[11] * m.v[14] - m.v[2] * m.v[5] * m.v[ 8] * m.v[15] + m.v[1] * m.v[6] * m.v[ 8] * m.v[15] +
		m.v[2] * m.v[4] * m.v[ 9] * m.v[15] - m.v[0] * m.v[6] * m.v[ 9] * m.v[15] - m.v[1] * m.v[4] * m.v[10] * m.v[15] + m.v[0] * m.v[5] * m.v[10] * m.v[15];

}

__forceinline bool has_mirroring(const Matrix4x4 &m) {
	return (determinant(m) < 0.0f);
}

__forceinline float & element(Matrix4x4 &m, int i, int j)
{
	return m.v[i*4 + j];
}

__forceinline const float & element(const Matrix4x4 &m, int i, int j)
{
	return m.v[i*4 + j];
}

__forceinline void transpose(Matrix4x4 &m)
{
	#define SWAP(a,b) {float temp = a; a = b; b = temp;}

	SWAP(m.v[1], m.v[4]);
	SWAP(m.v[2], m.v[8]);
	SWAP(m.v[3], m.v[12]);
	SWAP(m.v[6], m.v[9]);
	SWAP(m.v[7], m.v[13]);
	SWAP(m.v[11], m.v[14]);

	#undef SWAP
}

// Vector3 helper access
__forceinline Vector3 &translation(Matrix4x4 &m) {
	return *reinterpret_cast<Vector3 *>(&m.v[tx]);
}
__forceinline Vector3 &x_axis(Matrix4x4 &m) {
	return *reinterpret_cast<Vector3 *>(&m.v[xx]);
}
__forceinline Vector3 &y_axis(Matrix4x4 &m) {
	return *reinterpret_cast<Vector3 *>(&m.v[yx]);
}
__forceinline Vector3 &z_axis(Matrix4x4 &m) {
	return *reinterpret_cast<Vector3 *>(&m.v[zx]);
}

__forceinline const Vector3 &translation(const Matrix4x4 &m) {
	return *reinterpret_cast<const Vector3 *>(&m.v[tx]);
}
__forceinline const Vector3 &x_axis(const Matrix4x4 &m){
	return *reinterpret_cast<const Vector3 *>(&m.v[xx]);
}
__forceinline const Vector3 &y_axis(const Matrix4x4 &m){
	return *reinterpret_cast<const Vector3 *>(&m.v[yx]);
}
__forceinline const Vector3 &z_axis(const Matrix4x4 &m){
	return *reinterpret_cast<const Vector3 *>(&m.v[zx]);
}

__forceinline Vector3 &forward_axis(Matrix4x4 &m) {
	return y_axis(m);
}
__forceinline Vector3 &up_axis(Matrix4x4 &m) {
	return z_axis(m);
}
__forceinline Vector3 &right_axis(Matrix4x4 &m) {
	return x_axis(m);
}

__forceinline const Vector3 &forward_axis(const Matrix4x4 &m){
	return y_axis(m);
}
__forceinline const Vector3 &up_axis(const Matrix4x4 &m){
	return z_axis(m);
}
__forceinline const Vector3 &right_axis(const Matrix4x4 &m){
	return x_axis(m);
}

__forceinline Vector3 &axis(Matrix4x4 &m, int i)
{
	return *reinterpret_cast<Vector3 *>(&m.v[xx] + i*4);
}

__forceinline const Vector3 &axis(const Matrix4x4 &m, int i)
{
	return *reinterpret_cast<const Vector3 *>(&m.v[xx] + i*4);
}

__forceinline Vector4 &row(Matrix4x4 &m, int i)
{
	return *reinterpret_cast<Vector4 *>(&m.v[xx] + i*4);
}

__forceinline const Vector4 &row(const Matrix4x4 &m, int i)
{
	return *reinterpret_cast<const Vector4 *>(&m.v[xx] + i*4);
}

__forceinline void set_translation(Matrix4x4 &m, const Vector3 &t)
{
	translation(m) = t;
}

__forceinline Vector3 transform(const Matrix4x4 &m, const Vector3 &p)
{
	Vector3 pt;
	pt.x = m.v[xx] * p.x + m.v[yx] * p.y + m.v[zx] * p.z + m.v[tx];
	pt.y = m.v[xy] * p.x + m.v[yy] * p.y + m.v[zy] * p.z + m.v[ty];
	pt.z = m.v[xz] * p.x + m.v[yz] * p.y + m.v[zz] * p.z + m.v[tz];
	return pt;
}

__forceinline Vector3 transform_without_translation(const Matrix4x4 &m, const Vector3 &p)
{
	Vector3 pt;
	pt.x = m.v[xx] * p.x + m.v[yx] * p.y + m.v[zx] * p.z;
	pt.y = m.v[xy] * p.x + m.v[yy] * p.y + m.v[zy] * p.z;
	pt.z = m.v[xz] * p.x + m.v[yz] * p.y + m.v[zz] * p.z;
	return pt;
}

__forceinline Vector4 transform(const Matrix4x4 &m, const Vector4 &p)
{
	Vector4 pt;
	pt.x = m.v[xx] * p.x + m.v[yx] * p.y + m.v[zx] * p.z + p.w * m.v[tx];
	pt.y = m.v[xy] * p.x + m.v[yy] * p.y + m.v[zy] * p.z + p.w * m.v[ty];
	pt.z = m.v[xz] * p.x + m.v[yz] * p.y + m.v[zz] * p.z + p.w * m.v[tz];
	pt.w = m.v[xw] * p.x + m.v[yw] * p.y + m.v[zw] * p.z + p.w * m.v[tw];
	return pt;
}

__forceinline Matrix4x4 rotation(const Matrix4x4 &m)
{
	Matrix4x4 out = m;
	out.v[xw] = out.v[yw] = out.v[zw] = out.v[tx] = out.v[ty] = out.v[tz] = 0;
	out.v[tw] = 1;
	return out;
}

__forceinline void set_rotation(Matrix4x4 &m, const Matrix4x4 &rot)
{
	x_axis(m) = x_axis(rot);
	y_axis(m) = y_axis(rot);
	z_axis(m) = z_axis(rot);
}

__forceinline Vector3 scale(const Matrix4x4 &m)
{
	Vector3 s;
	s.x = length(x_axis(m));
	s.y = length(y_axis(m));
	s.z = length(z_axis(m));
	return s;
}

__forceinline void set_scale(Matrix4x4 &m, const Vector3 &s)
{
	Vector3 p = scale(m);
	x_axis(m) *= s.x / p.x;
	y_axis(m) *= s.y / p.y;
	z_axis(m) *= s.z / p.z;
}

inline Matrix4x4 inverse(const Matrix4x4 &m)
{
	Matrix4x4 inv = matrix4x4_identity();
	Matrix4x4 temp = m;
	int i, j, k, swap;
	float *v = (float *)&temp.v[xx];
	float *v2 = (float *)&inv.v[xx];
	for(i=0; i!=4; ++i) {
		swap=i;
		for(j=i+1; j!=4; ++j) {
			if(fabs(v[(j<<2)+i]) > fabs(v[(swap<<2)+i]))
				swap = j;
		}
		if (swap != i) {
			for(k=0; k!=4; ++k) {
				const float t = v[(i<<2)+k];
				v[(i<<2)+k] = v[(swap<<2)+k];
				v[(swap<<2)+k] = t;

				const float t2 = v2[(i<<2)+k];
				v2[(i<<2)+k] = v2[(swap<<2)+k];
				v2[(swap<<2)+k] = t2;
			}
		}
		if (v[(i<<2)+i] == 0)
			return inv;
		const float t = v[(i<<2)+i];
		for (k=0; k!=4; ++k) {
			v[(i<<2)+k] /= t;
			v2[(i<<2)+k] /= t;
		}
		for (j=0; j!=4; ++j) {
			if(j!=i) {
				const float t = v[(j<<2)+i];
				for(k=0; k<4; k++) {
					v[(j<<2)+k] -= v[(i<<2)+k]*t;
					v2[(j<<2)+k] -= v2[(i<<2)+k]*t;
				}
			}
		}
	}
	return inv;
}

}
