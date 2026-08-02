class PlayerTemplate
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

class PlayerTemplateInsertOverflowShim
{
public:
	void insert_overflow(PlayerTemplate * pos, const PlayerTemplate & x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<PlayerTemplate, allocator<PlayerTemplate> >::_M_insert_overflow(
	PlayerTemplate * pos, const PlayerTemplate & x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((PlayerTemplateInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
