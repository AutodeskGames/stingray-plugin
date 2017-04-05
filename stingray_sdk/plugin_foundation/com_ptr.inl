namespace stingray_plugin_foundation {

#if defined(WINDOWSPC) || defined(XBOXONE)

template<typename T>
ComPtr<T>::ComPtr(T* ptr = 0)  :  _owned(true), _ptr(ptr) {

}

template<typename T>
ComPtr<T>::ComPtr(const ComPtr<T>& rhs) : _owned(rhs._owned), _ptr(rhs.abandon()) {

}

template<typename T>
ComPtr<T>::~ComPtr() {
	if(_owned && _ptr) {
		_ptr->Release();
	}

}

template<typename T>
ComPtr<T>& ComPtr<T>::operator=(const ComPtr<T>& rhs) {
	if( this != &rhs ) {
		if( _ptr != rhs.get() && _owned && _ptr)
			_ptr->Release();
		_owned = rhs._owned;
		_ptr = rhs.abandon();
	}
	return *this;
}

template<typename T>
T& ComPtr<T>::operator*() const {
	return *get();
}

template<typename T>
T* ComPtr<T>::operator->() const {
	return get();
}

template<typename T>
T* ComPtr<T>::get() const {
	return _ptr;
}

template<typename T>
T* ComPtr<T>::abandon() const {
	_owned=false;
	return _ptr;
}

template<typename T>
T** ComPtr<T>::init_ptr() {
	if(_owned && _ptr)
		_ptr->Release();
	_ptr=0;
	_owned=true;
	return &_ptr;
}

#endif

}
