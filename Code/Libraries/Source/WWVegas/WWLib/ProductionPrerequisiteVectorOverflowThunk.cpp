class ProductionPrerequisite
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

class ProductionPrerequisiteInsertOverflowShim
{
public:
	void insert_overflow(ProductionPrerequisite * pos, const ProductionPrerequisite & x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<ProductionPrerequisite, allocator<ProductionPrerequisite> >::_M_insert_overflow(
	ProductionPrerequisite * pos, const ProductionPrerequisite & x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((ProductionPrerequisiteInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
