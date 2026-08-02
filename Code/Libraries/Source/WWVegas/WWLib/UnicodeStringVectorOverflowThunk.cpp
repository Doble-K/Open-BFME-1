class UnicodeString
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

class UnicodeStringInsertOverflowShim
{
public:
	void insert_overflow(UnicodeString * pos, const UnicodeString & x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<UnicodeString, allocator<UnicodeString> >::_M_insert_overflow(
	UnicodeString * pos, const UnicodeString & x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((UnicodeStringInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
