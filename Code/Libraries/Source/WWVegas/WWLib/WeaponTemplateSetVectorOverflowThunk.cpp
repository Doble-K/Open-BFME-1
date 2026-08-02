class WeaponTemplateSet
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

class WeaponTemplateSetInsertOverflowShim
{
public:
	void insert_overflow(WeaponTemplateSet *pos, const WeaponTemplateSet &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<WeaponTemplateSet, allocator<WeaponTemplateSet> >::_M_insert_overflow(
	WeaponTemplateSet *pos, const WeaponTemplateSet &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((WeaponTemplateSetInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
