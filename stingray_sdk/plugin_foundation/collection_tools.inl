namespace stingray_plugin_foundation {

template <class T>
inline void swap_erase(T &v, typename T::iterator it)
{
	std::swap(*it, v.back());
	v.pop_back();
}

template <class T>
inline void swap_erase(T &v, int i)
{
	swap_erase(v, v.begin() + i);
}

} // namespace stingray_plugin_foundation
