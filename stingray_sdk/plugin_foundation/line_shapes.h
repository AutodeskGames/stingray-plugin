#pragma once

#include "vector.h"
#include "types.h"
#include "color.h"

namespace stingray_plugin_foundation
{

namespace line_shapes
{
	typedef Vector<Vector3> PointList;
	typedef Vector<Color8> ColorList;

	void line(const Vector3 &p1, const Vector3 &p2, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors);
	void xyz_cross(const Vector3 &pos, float radius, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors);
	void circle(const Vector3 &pos, float radius, const Vector3 &normal, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors, int segments=20);
	void cone(const Vector3 &p1, const Vector3 &p2, float radius, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors, int segments = 20, int bars = 10);
	void arrow(const Vector3 &from, const Vector3 &to, float head_height, float head_radius, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors);
	void sphere(const Vector3 &pos, float radius, Color8 color, PointList & out_starts, PointList & out_ends, ColorList & out_colors, int segments = 20, int parts = 2);
} // namespace line_shapes

} // namespace stingray_plugin_foundation

#include "line_shapes.inl"
