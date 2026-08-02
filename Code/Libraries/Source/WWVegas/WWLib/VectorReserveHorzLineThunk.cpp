struct HorzLine
{
};

struct ICoord2D
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
public:
	void reserve(unsigned int);
	void resize(unsigned int);
};

class HorzLineVectorReserveShim
{
public:
	void reserve(unsigned int n);
};

class ICoord2DVectorResizeShim
{
public:
	void resize(unsigned int n);
};

template <class Type, class Allocator>
void vector<Type, Allocator>::reserve(unsigned int n)
{
	((HorzLineVectorReserveShim *)this)->reserve(n);
}

template void vector<HorzLine, allocator<HorzLine> >::reserve(unsigned int);

template <class Type, class Allocator>
void vector<Type, Allocator>::resize(unsigned int n)
{
	((ICoord2DVectorResizeShim *)this)->resize(n);
}

template void vector<ICoord2D, allocator<ICoord2D> >::resize(unsigned int);
}
