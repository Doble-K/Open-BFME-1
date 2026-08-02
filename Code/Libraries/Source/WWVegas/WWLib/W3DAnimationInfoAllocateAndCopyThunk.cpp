class W3DAnimationInfo
{
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	template <class Iterator>
	Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
	void _M_clear();
};

class W3DAnimationInfoAllocateAndCopyShim
{
public:
	W3DAnimationInfo *allocate_and_copy(unsigned int n, const W3DAnimationInfo *first, const W3DAnimationInfo *last);
	void clear();
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(unsigned int n, Iterator first, Iterator last)
{
	return (Type *)((W3DAnimationInfoAllocateAndCopyShim *)this)->allocate_and_copy(
		n, (const W3DAnimationInfo *)first, (const W3DAnimationInfo *)last);
}

template W3DAnimationInfo *vector<W3DAnimationInfo, allocator<W3DAnimationInfo> >::_M_allocate_and_copy<W3DAnimationInfo const *>(
	unsigned int, W3DAnimationInfo const *, W3DAnimationInfo const *);

void vector<W3DAnimationInfo, allocator<W3DAnimationInfo> >::_M_clear()
{
	((W3DAnimationInfoAllocateAndCopyShim *)this)->clear();
}
}
