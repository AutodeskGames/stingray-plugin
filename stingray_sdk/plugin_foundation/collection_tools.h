#pragma once

#include "pair.h"
#include "vector"

namespace stingray_plugin_foundation {

template <class T>
inline void swap_erase(T &v, typename T::iterator it);

template <class T>
inline void swap_erase(T &v, int i);

} // namespace stingray_plugin_foundation

#include "collection_tools.inl"
