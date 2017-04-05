#include "math.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Vector4 operator / (const Vector4 &lhs, const Vector4 &rhs) {
	return vector4(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z, lhs.w/rhs.w);
}

__forceinline Vector4 operator * (const Vector4 &lhs, const Vector4 &rhs) {
	return vector4(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z, lhs.w*rhs.w);
}

__forceinline Vector4 operator + (const Vector4 &lhs, const Vector4 &rhs) {
	return vector4(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z, lhs.w+rhs.w);
}

__forceinline Vector4 operator - (const Vector4 &lhs, const Vector4 &rhs) {
	return vector4(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z, lhs.w-rhs.w);
}

__forceinline Vector4 operator - (const Vector4 &v) {
	return vector4(-v.x, -v.y, -v.z, -v.w);
}

__forceinline Vector4 operator + (const Vector4 &v) {
	return v;
}

__forceinline void operator /= (Vector4 &lhs, const Vector4 &rhs) {
	lhs.x/=rhs.x; lhs.y/=rhs.y; lhs.z/=rhs.z; lhs.w/=rhs.w;
}

__forceinline void operator *= (Vector4 &lhs, const Vector4 &rhs) {
	lhs.x*=rhs.x; lhs.y*=rhs.y; lhs.z*=rhs.z; lhs.w*=rhs.w;
}

__forceinline void operator += (Vector4 &lhs, const Vector4 &rhs) {
	lhs.x+=rhs.x; lhs.y+=rhs.y; lhs.z+=rhs.z; lhs.w+=rhs.w;
}

__forceinline void operator -= (Vector4 &lhs, const Vector4 &rhs) {
	lhs.x-=rhs.x; lhs.y-=rhs.y; lhs.z-=rhs.z; lhs.w-=rhs.w;
}

__forceinline Vector4 operator/(const Vector4 &lhs, float rhs) {
	return vector4(lhs.x/rhs, lhs.y/rhs, lhs.z/rhs, lhs.w/rhs);
}

__forceinline Vector4 operator*(const Vector4 &lhs, float rhs) {
	return vector4(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs, lhs.w*rhs);
}

__forceinline Vector4 operator*(float lhs, const Vector4 &rhs) {
	return vector4(rhs.x*lhs, rhs.y*lhs, rhs.z*lhs, rhs.w*lhs);
}

__forceinline Vector4 operator+(const Vector4 &lhs, float rhs) {
	return vector4(lhs.x+rhs, lhs.y+rhs, lhs.z+rhs, lhs.w+rhs);
}

__forceinline Vector4 operator-(const Vector4 &lhs, float rhs) {
	return vector4(lhs.x-rhs, lhs.y-rhs, lhs.z-rhs, lhs.w-rhs);
}

__forceinline void operator/=(Vector4 &lhs, float rhs) {
	lhs.x/=rhs; lhs.y/=rhs; lhs.z/=rhs; lhs.w/=rhs;
}

__forceinline void operator*=(Vector4 &lhs, float rhs) {
	lhs.x*=rhs; lhs.y*=rhs; lhs.z*=rhs; lhs.w*=rhs;
}

__forceinline void operator+=(Vector4 &lhs, float rhs) {
	lhs.x+=rhs; lhs.y+=rhs; lhs.z+=rhs; lhs.w+=rhs;
}

__forceinline void operator-=(Vector4 &lhs, float rhs) {
	lhs.x-=rhs; lhs.y-=rhs; lhs.z-=rhs; lhs.w-=rhs;
}

__forceinline bool operator==(const Vector4 &lhs, const Vector4 &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

__forceinline bool operator!=(const Vector4 &lhs, const Vector4 &rhs)
{
	return !(lhs == rhs);
}

// Methods
__forceinline Vector4 vector4(float x, float y, float z, float w) {
	Vector4 v;
	v.x = x; v.y = y; v.z = z; v.w = w;
	return v;
}

__forceinline Vector4 vector4_base(int i)
{
	if (i==0)
		return vector4(1,0,0,0);
	else if (i==1)
		return vector4(0,1,0,0);
	else if (i==2)
		return vector4(0,0,1,0);
	else if (i==3)
		return vector4(0,0,0,1);
	return vector4(0,0,0,0);
}

__forceinline float & element(Vector4 &v, int i)
{
	return *(&v.x + i);
}

__forceinline const float & element(const Vector4 &v, int i)
{
	return *(&v.x + i);
}

__forceinline void zero(Vector4 &v) {
	v.x=0.f; v.y=0.f; v.z=0.f; v.w = 0.f;
}

__forceinline float length(const Vector4 &v) {
	return math::square_root(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

__forceinline float norm(const Vector4 &v)
{
	return math::square_root(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

__forceinline float one_norm(const Vector4 &v)
{
	return math::abs(v.x) + math::abs(v.y) + math::abs(v.z) + math::abs(v.w);
}

__forceinline float infinity_norm(const Vector4 &v)
{
	return math::max( math::max(math::abs(v.x), math::abs(v.y)), math::max(math::abs(v.z), math::abs(v.w) ));
}

__forceinline Vector4 normalize(const Vector4 &v) {
	float l=length(v);
	if (l<0.0001)
		return vector4(0.f, 0.f, 0.f, 0.f);
	return v / l;
}

__forceinline float dot(const Vector4 &v0, const Vector4 &v1) {
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
}

__forceinline float distance(const Vector4 &v0, const Vector4 &v1) {
	Vector4	tmp = vector4(v0.x-v1.x,v0.y-v1.y,v0.z-v1.z,v0.w-v1.w);
	return length(tmp);
}

__forceinline float distance_squared(const Vector4 &v0, const Vector4 &v1) {
	return (v0.x-v1.x)*(v0.x-v1.x) + (v0.y-v1.y)*(v0.y-v1.y) + (v0.z-v1.z)*(v0.z-v1.z) + (v0.w-v1.w)*(v0.w-v1.w);
}

__forceinline Vector4 orthonormalize(const Vector4 &v, const Vector4 &ref)
{
	Vector4 res = v - dot(v, ref) * ref;
	return normalize(res);
}

__forceinline Vector4 min(const Vector4 &v0, const Vector4 &v1)
{
	return vector4(math::min(v0.x,v1.x), math::min(v0.y,v1.y), math::min(v0.z,v1.z), math::min(v0.w,v1.w));
}

__forceinline Vector4 max(const Vector4 &v0, const Vector4 &v1)
{
	return vector4(math::max(v0.x,v1.x), math::max(v0.y,v1.y), math::max(v0.z,v1.z), math::max(v0.w,v1.w));
}

__forceinline Vector4 lerp(const Vector4 &a, const Vector4 &b, float p)
{
	return a * (1-p) + b * p;
}

__forceinline Vector3 vector3(const Vector4 &a)
{
	Vector3 v;
	v.x = a.x; v.y = a.y; v.z = a.z;
	return v;
}

}
