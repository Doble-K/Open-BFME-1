class W3DAnimationInfo
{
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
};

class W3DAnimationInfoInsertOverflowShim
{
public:
	void insert_overflow(W3DAnimationInfo * pos, const W3DAnimationInfo & x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<W3DAnimationInfo, allocator<W3DAnimationInfo> >::_M_insert_overflow(
	W3DAnimationInfo * pos, const W3DAnimationInfo & x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((W3DAnimationInfoInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
