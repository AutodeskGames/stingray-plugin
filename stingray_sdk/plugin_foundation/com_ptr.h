#pragma once

#if defined(WINDOWSPC) || defined(XBOXONE)

namespace stingray_plugin_foundation {

template<typename T>
class ComPtr {
public:
	explicit ComPtr(T* ptr = 0);
	ComPtr(const ComPtr<T>& rhs);
	~ComPtr();

	ComPtr<T>& operator=(const ComPtr<T>& rhs);
	T& operator*() const;
	T* operator->() const;
	T* get() const;

	T* abandon() const;
	T** init_ptr();
private:
	T* _ptr;
	mutable bool _owned;
};

#endif

}

#include "com_ptr.inl"

