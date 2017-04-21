#include "math.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Vector3 operator / (const Vector3 &lhs, const Vector3 &rhs) {
	return vector3(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z);
}

__forceinline Vector3 operator * (const Vector3 &lhs, const Vector3 &rhs) {
	return vector3(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z);
}

__forceinline Vector3 operator + (const Vector3 &lhs, const Vector3 &rhs) {
	return vector3(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}

__forceinline Vector3 operator - (const Vector3 &lhs, const Vector3 &rhs) {
	return vector3(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z);
}

__forceinline Vector3 operator - (const Vector3 &v) {
	return vector3(-v.x, -v.y, -v.z);
}

__forceinline Vector3 operator + (const Vector3 &v) {
	return v;
}

__forceinline void operator /= (Vector3 &lhs, const Vector3 &rhs) {
	lhs.x/=rhs.x; lhs.y/=rhs.y; lhs.z/=rhs.z;
}

__forceinline void operator *= (Vector3 &lhs, const Vector3 &rhs) {
	lhs.x*=rhs.x; lhs.y*=rhs.y; lhs.z*=rhs.z;
}

__forceinline void operator += (Vector3 &lhs, const Vector3 &rhs) {
	lhs.x+=rhs.x; lhs.y+=rhs.y; lhs.z+=rhs.z;
}

__forceinline void operator -= (Vector3 &lhs, const Vector3 &rhs) {
	lhs.x-=rhs.x; lhs.y-=rhs.y; lhs.z-=rhs.z;
}

__forceinline Vector3 operator/(const Vector3 &lhs, float rhs) {
	return vector3(lhs.x/rhs, lhs.y/rhs, lhs.z/rhs);
}

__forceinline Vector3 operator*(const Vector3 &lhs, float rhs) {
	return vector3(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs);
}

__forceinline Vector3 operator*(float lhs, const Vector3 &rhs) {
	return vector3(rhs.x*lhs, rhs.y*lhs, rhs.z*lhs);
}

__forceinline Vector3 operator+(const Vector3 &lhs, float rhs) {
	return vector3(lhs.x+rhs, lhs.y+rhs, lhs.z+rhs);
}

__forceinline Vector3 operator-(const Vector3 &lhs, float rhs) {
	return vector3(lhs.x-rhs, lhs.y-rhs, lhs.z-rhs);
}

__forceinline void operator/=(Vector3 &lhs, float rhs) {
	lhs.x/=rhs; lhs.y/=rhs; lhs.z/=rhs;
}

__forceinline void operator*=(Vector3 &lhs, float rhs) {
	lhs.x*=rhs; lhs.y*=rhs; lhs.z*=rhs;
}

__forceinline void operator+=(Vector3 &lhs, float rhs) {
	lhs.x+=rhs; lhs.y+=rhs; lhs.z+=rhs;
}

__forceinline void operator-=(Vector3 &lhs, float rhs) {
	lhs.x-=rhs; lhs.y-=rhs; lhs.z-=rhs;
}

__forceinline bool operator==(const Vector3 &lhs, const Vector3 &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

__forceinline bool operator!=(const Vector3 &lhs, const Vector3 &rhs)
{
	return !(lhs == rhs);
}

__forceinline bool operator< (const Vector3 &lhs, const Vector3 &rhs)
{
	if (lhs.x != rhs.x) return lhs.x < rhs.x;
	if (lhs.y != rhs.y) return lhs.y < rhs.y;
	return lhs.z < rhs.z;
}

__forceinline bool operator<=(const Vector3 &lhs, const Vector3 &rhs)
{
	return (lhs < rhs) || (lhs == rhs);
}

__forceinline bool operator> (const Vector3 &lhs, const Vector3 &rhs)
{
	return (rhs < lhs);
}

__forceinline bool operator>=(const Vector3 &lhs, const Vector3 &rhs)
{
	return !(lhs < rhs);
}

// Methods
__forceinline Vector3 vector3(float x, float y, float z) {
	Vector3 v = {x, y, z};
	return v;
}

__forceinline Vector3 vector3(const float v[3])
{
	Vector3 r = {v[0], v[1], v[2]};
	return r;
}

__forceinline Vector3 vector3(const Vector2 &v) {
	Vector3 r = { v.x, v.y, 0.f };
	return r;
}

__forceinline Vector3 vector3(const Vector2 &v, float z) {
	Vector3 r = { v.x, v.y, z };
	return r;
}

__forceinline Vector3 vector3_base(int i)
{
	if (i==0)
		return vector3(1,0,0);
	else if (i==1)
		return vector3(0,1,0);
	else if (i==2)
		return vector3(0,0,1);
	return vector3(0,0,0);
}

__forceinline float & element(Vector3 &v, int i)
{
	return *(&v.x + i);
}

__forceinline const float & element(const Vector3 &v, int i)
{
	return *(&v.x + i);
}

__forceinline void zero(Vector3 &v) {
	v.x=0.f; v.y=0.f; v.z=0.f;
}

__forceinline bool is_zero(const Vector3 &v)
{
	return v.x == 0.0f && v.y == 0.0f && v.z == 0.0f;
}

__forceinline bool is_zero(const Vector3 &v, float eps)
{
	return length_squared(v) <= eps*eps;
}

__forceinline float length(const Vector3 &v) {
	return math::square_root(v.x*v.x + v.y*v.y + v.z*v.z);
}

__forceinline float length_squared(const Vector3 &v) {
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

__forceinline float norm(const Vector3 &v)
{
	return math::square_root(v.x*v.x + v.y*v.y + v.z*v.z);
}

__forceinline float one_norm(const Vector3 &v)
{
	return math::abs(v.x) + math::abs(v.y) + math::abs(v.z);
}

__forceinline float infinity_norm(const Vector3 &v)
{
	return math::max3( math::abs(v.x), math::abs(v.y), math::abs(v.z) );
}

__forceinline Vector3 normalize(const Vector3 &v) {
	float l=length(v);
	if (l<0.0001)
		return vector3(0.f, 0.f, 0.f);
	return v / l;
}

__forceinline float dot(const Vector3 &v0, const Vector3 &v1) {
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

__forceinline Vector3 cross(const Vector3 &v0, const Vector3 &v1) {
	return vector3((v0.y*v1.z)-(v0.z*v1.y),(v0.z*v1.x)-(v0.x*v1.z),(v0.x*v1.y)-(v0.y*v1.x));
}

__forceinline float distance(const Vector3 &v0, const Vector3 &v1) {
	Vector3	tmp = vector3(v0.x-v1.x,v0.y-v1.y,v0.z-v1.z);
	return length(tmp);
}

__forceinline float distance_squared(const Vector3 &v0, const Vector3 &v1) {
	return (v0.x-v1.x)*(v0.x-v1.x) + (v0.y-v1.y)*(v0.y-v1.y) + (v0.z-v1.z)*(v0.z-v1.z);
}

__forceinline Vector3 normal_vector(const Vector3 &v0,const Vector3 &v1, const Vector3& v2){
	return cross(v1-v0,v2-v0);
}

__forceinline Vector3 orthonormalize(const Vector3 &v, const Vector3 &ref)
{
	Vector3 res = v - dot(v, ref) * ref;
	return normalize(res);
}

__forceinline Vector3 min(const Vector3 &v0, const Vector3 &v1)
{
	return vector3(math::min(v0.x,v1.x), math::min(v0.y,v1.y), math::min(v0.z,v1.z));
}

__forceinline Vector3 max(const Vector3 &v0, const Vector3 &v1)
{
	return vector3(math::max(v0.x,v1.x), math::max(v0.y,v1.y), math::max(v0.z,v1.z));
}

__forceinline bool all_gt(const Vector3& p1, const Vector3& p2)
{
	return p1.x > p2.x && p1.y > p2.y && p1.z > p2.z;
}

__forceinline bool all_lt(const Vector3& p1, const Vector3& p2)
{
	return p1.x < p2.x && p1.y < p2.y && p1.z < p2.z;
}

__forceinline void make_axes(const Vector3 &x, Vector3 &y, Vector3 &z)
{
	if (x.z > -0.5 && x.z < 0.5) {
		y = vector3(-x.y, x.x, 0);
		y = orthonormalize(y, x);
		z = cross(x, y);
	} else {
		y = vector3(0, x.z, -x.y);
		y = orthonormalize(y, x);
		z = cross(x,y);
	}
}

__forceinline Vector3 lerp(const Vector3 &a, const Vector3 &b, float p)
{
	return a * (1-p) + b * p;
}

__forceinline MagnitudeAndDirection magnitude_and_direction(const Vector3 &v)
{
	MagnitudeAndDirection md;
	md.magnitude = norm(v);
	md.direction = md.magnitude > 0 ? v / md.magnitude : vector3(0,0,0);
	return md;
}

}
