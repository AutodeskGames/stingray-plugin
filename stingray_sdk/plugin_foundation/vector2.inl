#include "math.h"

namespace stingray_plugin_foundation {

// Operators
__forceinline Vector2 operator / (const Vector2 &lhs, const Vector2 &rhs) {
	return vector2(lhs.x/rhs.x, lhs.y/rhs.y);
}

__forceinline Vector2 operator * (const Vector2 &lhs, const Vector2 &rhs) {
	return vector2(lhs.x*rhs.x, lhs.y*rhs.y);
}

__forceinline Vector2 operator + (const Vector2 &lhs, const Vector2 &rhs) {
	return vector2(lhs.x+rhs.x, lhs.y+rhs.y);
}

__forceinline Vector2 operator - (const Vector2 &lhs, const Vector2 &rhs) {
	return vector2(lhs.x-rhs.x, lhs.y-rhs.y);
}

__forceinline Vector2 operator - (const Vector2 &v) {
	return vector2(-v.x, -v.y);
}

__forceinline Vector2 operator + (const Vector2 &v) {
	return v;
}

__forceinline void operator /= (Vector2 &lhs, const Vector2 &rhs) {
	lhs.x/=rhs.x; lhs.y/=rhs.y;
}

__forceinline void operator *= (Vector2 &lhs, const Vector2 &rhs) {
	lhs.x*=rhs.x; lhs.y*=rhs.y;
}

__forceinline void operator += (Vector2 &lhs, const Vector2 &rhs) {
	lhs.x+=rhs.x; lhs.y+=rhs.y;
}

__forceinline void operator -= (Vector2 &lhs, const Vector2 &rhs) {
	lhs.x-=rhs.x; lhs.y-=rhs.y;
}

__forceinline Vector2 operator/(const Vector2 &lhs, float rhs) {
	return vector2(lhs.x/rhs, lhs.y/rhs);
}

__forceinline Vector2 operator*(const Vector2 &lhs, float rhs) {
	return vector2(lhs.x*rhs, lhs.y*rhs);
}

__forceinline Vector2 operator*(float lhs, const Vector2 &rhs) {
	return vector2(rhs.x*lhs, rhs.y*lhs);
}

__forceinline Vector2 operator+(const Vector2 &lhs, float rhs) {
	return vector2(lhs.x+rhs, lhs.y+rhs);
}

__forceinline Vector2 operator-(const Vector2 &lhs, float rhs) {
	return vector2(lhs.x-rhs, lhs.y-rhs);
}

__forceinline void operator/=(Vector2 &lhs, float rhs) {
	lhs.x/=rhs; lhs.y/=rhs;
}

__forceinline void operator*=(Vector2 &lhs, float rhs) {
	lhs.x*=rhs; lhs.y*=rhs;
}

__forceinline void operator+=(Vector2 &lhs, float rhs) {
	lhs.x+=rhs; lhs.y+=rhs;
}

__forceinline void operator-=(Vector2 &lhs, float rhs) {
	lhs.x-=rhs; lhs.y-=rhs;
}

__forceinline bool operator==(const Vector2 &lhs, const Vector2 &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

__forceinline bool operator!=(const Vector2 &lhs, const Vector2 &rhs)
{
	return !(lhs == rhs);
}

// Methods
__forceinline Vector2 vector2(float x, float y) {
	Vector2 v;
	v.x = x;
	v.y = y;
	return v;
}

__forceinline float & element(Vector2 &v, int i)
{
	return *(&v.x + i);
}

__forceinline const float & element(const Vector2 &v, int i)
{
	return *(&v.x + i);
}

__forceinline bool is_zero(const Vector2 &v)
{
	return v.x == 0.0f && v.y == 0.0f;
}

__forceinline bool is_zero(const Vector2 &v, float eps)
{
	return length_squared(v) <= eps*eps;
}

__forceinline void zero(Vector2 &v) {
	v.x=0.f; v.y=0.f;
}

__forceinline float length(const Vector2 &v) {
	return math::square_root(v.x*v.x + v.y*v.y);
}

__forceinline float length_squared(const Vector2 &v) {
	return v.x*v.x + v.y*v.y;
}

__forceinline Vector2 normalize(const Vector2 &v) {
	float l=length(v);
	if (l<0.0001)
		return vector2(0.f, 0.f);
	return v / l;
}

__forceinline float dot(const Vector2 &v0, const Vector2 &v1) {
	return v0.x * v1.x + v0.y * v1.y;
}

__forceinline float distance(const Vector2 &v0, const Vector2 &v1) {
	Vector2	tmp = vector2(v0.x-v1.x,v0.y-v1.y);
	return length(tmp);
}

__forceinline float distance_squared(const Vector2 &v0, const Vector2 &v1) {
	return (v0.x-v1.x)*(v0.x-v1.x) + (v0.y-v1.y)*(v0.y-v1.y);
}

__forceinline Vector2 lerp(const Vector2 &a, const Vector2 &b, float p)
{
	return a * (1-p) + b * p;
}

__forceinline Vector2 min(const Vector2 &v0, const Vector2 &v1)
{
	return vector2(math::min(v0.x,v1.x), math::min(v0.y,v1.y));
}

__forceinline Vector2 max(const Vector2 &v0, const Vector2 &v1)
{
	return vector2(math::max(v0.x,v1.x), math::max(v0.y,v1.y));
}

}
