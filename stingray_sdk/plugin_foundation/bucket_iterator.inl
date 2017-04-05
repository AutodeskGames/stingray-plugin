namespace stingray_plugin_foundation {

// ----------------------------------------------------------------------
// BucketIterator
// ----------------------------------------------------------------------

template <class CONTAINER, class ITEM>
BucketIterator<CONTAINER, ITEM>::BucketIterator(CONTAINER &container, unsigned int i) : _container(&container), _i(i)
{
	advance_to_valid_bucket();
}

template <class CONTAINER, class ITEM>
BucketIterator<CONTAINER, ITEM>::BucketIterator(const iterator &other) : _container(other._container), _i(other._i)
{}

template <class CONTAINER, class ITEM>
BucketIterator<CONTAINER, ITEM> BucketIterator<CONTAINER, ITEM>::operator++()
{
	//XASSERT(_i < _container->num_buckets(), "iterating past end of container");
	XENSURE(_i < _container->num_buckets());
	++_i;
	advance_to_valid_bucket();
	return *this;
}

template <class CONTAINER, class ITEM>
BucketIterator<CONTAINER, ITEM> BucketIterator<CONTAINER, ITEM>::operator++(int)
{
	iterator result = *this;
	++(*this);
	return result;
}

template <class CONTAINER, class ITEM>
void BucketIterator<CONTAINER, ITEM>::advance_to_valid_bucket()
{
	unsigned int size = _container->num_buckets();
	for (; _i < size; ++_i)
		if (_container->bucket_valid(_i))
			break;
}

// ----------------------------------------------------------------------
// ConstBucketIterator
// ----------------------------------------------------------------------


template <class CONTAINER, class ITEM>
ConstBucketIterator<CONTAINER, ITEM>::ConstBucketIterator(const CONTAINER &container, unsigned int i) : _container(&container), _i(i)
{
	advance_to_valid_bucket();
}

template <class CONTAINER, class ITEM>
ConstBucketIterator<CONTAINER, ITEM>::ConstBucketIterator(const iterator &other) : _container(other._container), _i(other._i)
{}

template <class CONTAINER, class ITEM>
ConstBucketIterator<CONTAINER, ITEM>::ConstBucketIterator(const BucketIterator<CONTAINER,ITEM> &other) : _container(other._container), _i(other._i)
{}

template <class CONTAINER, class ITEM>
ConstBucketIterator<CONTAINER, ITEM> ConstBucketIterator<CONTAINER, ITEM>::operator++()
{
	XASSERT(_i < _container->num_buckets(), "iterating past end of container");
	++_i;
	advance_to_valid_bucket();
	return *this;
}

template <class CONTAINER, class ITEM>
ConstBucketIterator<CONTAINER, ITEM> ConstBucketIterator<CONTAINER, ITEM>::operator++(int)
{
	iterator result = *this;
	++(*this);
	return result;
}

template <class CONTAINER, class ITEM>
void ConstBucketIterator<CONTAINER, ITEM>::advance_to_valid_bucket()
{
	unsigned int size = _container->num_buckets();
	for (; _i < size; ++_i)
		if (_container->bucket_valid(_i))
			break;
}

} // namespace stingray_plugin_foundation
