class Object
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
};

class ObjectPointerAllocateAndCopyShim
{
public:
	Object **allocate_and_copy(unsigned int n, Object *const *first, Object *const *last);
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(unsigned int n, Iterator first, Iterator last)
{
	return (Type *)((ObjectPointerAllocateAndCopyShim *)this)->allocate_and_copy(
		n, (Object *const *)first, (Object *const *)last);
}

template Object **vector<Object *, allocator<Object *> >::_M_allocate_and_copy<Object *const *>(
	unsigned int, Object *const *, Object *const *);
}
