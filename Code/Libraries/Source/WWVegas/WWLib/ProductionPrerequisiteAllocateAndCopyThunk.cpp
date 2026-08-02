class ProductionPrerequisite
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

class ProductionPrerequisiteAllocateAndCopyShim
{
public:
	ProductionPrerequisite *allocate_and_copy(unsigned int n, const ProductionPrerequisite *first, const ProductionPrerequisite *last);
	void clear();
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(unsigned int n, Iterator first, Iterator last)
{
	return (Type *)((ProductionPrerequisiteAllocateAndCopyShim *)this)->allocate_and_copy(
		n, (const ProductionPrerequisite *)first, (const ProductionPrerequisite *)last);
}

template ProductionPrerequisite *vector<ProductionPrerequisite, allocator<ProductionPrerequisite> >::_M_allocate_and_copy<ProductionPrerequisite const *>(
	unsigned int, ProductionPrerequisite const *, ProductionPrerequisite const *);

void vector<ProductionPrerequisite, allocator<ProductionPrerequisite> >::_M_clear()
{
	((ProductionPrerequisiteAllocateAndCopyShim *)this)->clear();
}
}
