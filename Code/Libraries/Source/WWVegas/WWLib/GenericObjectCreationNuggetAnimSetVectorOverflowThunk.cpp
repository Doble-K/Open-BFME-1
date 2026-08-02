struct GenericObjectCreationNugget
{
	struct AnimSet
	{
	};
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

class GenericObjectCreationNuggetAnimSetInsertOverflowShim
{
public:
	void insert_overflow(GenericObjectCreationNugget::AnimSet *pos, const GenericObjectCreationNugget::AnimSet &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<GenericObjectCreationNugget::AnimSet, allocator<GenericObjectCreationNugget::AnimSet> >::_M_insert_overflow(
	GenericObjectCreationNugget::AnimSet *pos, const GenericObjectCreationNugget::AnimSet &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((GenericObjectCreationNuggetAnimSetInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
