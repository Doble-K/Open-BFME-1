struct ParticleSysBoneInfo
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

class ParticleSysBoneInfoAllocateAndCopyShim
{
public:
	ParticleSysBoneInfo *allocate_and_copy(unsigned int n, const ParticleSysBoneInfo *first, const ParticleSysBoneInfo *last);
	void clear();
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(unsigned int n, Iterator first, Iterator last)
{
	return (Type *)((ParticleSysBoneInfoAllocateAndCopyShim *)this)->allocate_and_copy(
		n, (const ParticleSysBoneInfo *)first, (const ParticleSysBoneInfo *)last);
}

template ParticleSysBoneInfo *vector<ParticleSysBoneInfo, allocator<ParticleSysBoneInfo> >::_M_allocate_and_copy<ParticleSysBoneInfo const *>(
	unsigned int, ParticleSysBoneInfo const *, ParticleSysBoneInfo const *);

void vector<ParticleSysBoneInfo, allocator<ParticleSysBoneInfo> >::_M_clear()
{
	((ParticleSysBoneInfoAllocateAndCopyShim *)this)->clear();
}
}
