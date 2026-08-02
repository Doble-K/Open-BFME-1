struct tConnInfoStruct
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

class tConnInfoStructInsertOverflowShim
{
public:
	void insert_overflow(tConnInfoStruct * pos, const tConnInfoStruct & x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<tConnInfoStruct, allocator<tConnInfoStruct> >::_M_insert_overflow(
	tConnInfoStruct * pos, const tConnInfoStruct & x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((tConnInfoStructInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
