#pragma once

namespace stingray_plugin_foundation {

struct less
{
	template <class A, class B> bool operator()(const A& a, const B& b) const {return (a < b);}
	void swap(less &other) {}
};

struct equal_to
{
	template <class A, class B> bool operator()(const A& a, const B& b) const {return (a == b);}
	void swap(less &other) {}
};

} // namespace stingray_plugin_foundation
