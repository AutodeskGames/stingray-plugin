#include "vector3.h"

namespace stingray_plugin_foundation
{

inline void line_shapes::line(const Vector3 &p1, const Vector3 &p2, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors)
{
	out_starts.push_back(p1);
	out_ends.push_back(p2);
	out_colors.push_back(color);
}

inline void line_shapes::xyz_cross(const Vector3 &pos, float radius, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors)
{
	line(pos - vector3(radius,0,0), pos + vector3(radius,0,0), color, out_starts, out_ends, out_colors);
	line(pos - vector3(0,radius,0), pos + vector3(0,radius,0), color, out_starts, out_ends, out_colors);
	line(pos - vector3(0,0,radius), pos + vector3(0,0,radius), color, out_starts, out_ends, out_colors);
}

inline void line_shapes::circle(const Vector3 &pos, float radius, const Vector3 &normal, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors, int segments)
{
	Vector3 x, y;
	make_axes(normal, x, y);
	x *= radius;
	y *= radius;

	Vector3 prev;
	for( int i = 0; i <= segments; ++i ) {
		float t = ((math::pi*2.0f) / ((float)segments)) * (float)i;
		Vector3 point = pos + x * cosf(t) + y * sinf(t);
		if (i != 0)
			line(prev, point, color, out_starts, out_ends, out_colors);
		prev = point;
	}
}

inline void line_shapes::cone(const Vector3 &p1, const Vector3 &p2, float radius, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors, int segments, int bars)
{
	Vector3 n = normalize(p1 - p2);
	Vector3 x, y;
	make_axes(n, x, y);

	circle(p2, radius, n, color, out_starts, out_ends, out_colors, segments);
	for (int i=0; i<bars; ++i) {
		float angle = (float(i)/float(bars)) * 2.0f * math::pi;
		Vector3 end = p2 + x*cosf(angle)*radius + y * sinf(angle)*radius;
		line(p1, end, color, out_starts, out_ends, out_colors);
	}
}

inline void line_shapes::arrow(const Vector3 &from, const Vector3 &to, float head_height, float head_radius, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors)
{
	const Vector3 line_normal = normalize(to - from);
	line(from, to, color, out_starts, out_ends, out_colors);
	cone(to, to - line_normal * head_height, head_radius, color, out_starts, out_ends, out_colors, 12, 6);
}

inline void line_shapes::sphere(const Vector3 &pos, float radius, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors, int segments, int parts)
{
	if (radius == 0)
		return;

	for (int i=0; i<parts; ++i) {
		float offset = radius*float(i)/float(parts);
		float r = sqrtf(radius*radius - offset*offset);
		int seg = int( float(segments) * r / radius + 0.5f);

		circle(pos + vector3(0,0,offset), r, vector3(0,0,1), color, out_starts, out_ends, out_colors, seg);
		circle(pos + vector3(0,offset,0), r, vector3(0,1,0), color, out_starts, out_ends, out_colors, seg);
		circle(pos + vector3(offset,0,0), r, vector3(1,0,0), color, out_starts, out_ends, out_colors, seg);

		if (i != 0) {
			circle(pos - vector3(0,0,offset), r, vector3(0,0,1), color, out_starts, out_ends, out_colors, seg);
			circle(pos - vector3(0,offset,0), r, vector3(0,1,0), color, out_starts, out_ends, out_colors, seg);
			circle(pos - vector3(offset,0,0), r, vector3(1,0,0), color, out_starts, out_ends, out_colors, seg);
		}
	}
}

}
