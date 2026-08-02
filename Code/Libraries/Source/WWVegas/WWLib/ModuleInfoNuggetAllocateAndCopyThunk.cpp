struct ModuleInfo
{
	struct Nugget
	{
	};
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

class ModuleInfoNuggetAllocateAndCopyShim
{
public:
	ModuleInfo::Nugget *allocate_and_copy(unsigned int n, const ModuleInfo::Nugget *first, const ModuleInfo::Nugget *last);
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(unsigned int n, Iterator first, Iterator last)
{
	return (Type *)((ModuleInfoNuggetAllocateAndCopyShim *)this)->allocate_and_copy(n, (const ModuleInfo::Nugget *)first, (const ModuleInfo::Nugget *)last);
}

template ModuleInfo::Nugget *vector<ModuleInfo::Nugget, allocator<ModuleInfo::Nugget> >::_M_allocate_and_copy<ModuleInfo::Nugget const *>(
	unsigned int, ModuleInfo::Nugget const *, ModuleInfo::Nugget const *);
}
