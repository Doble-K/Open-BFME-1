struct ModuleInfo
{
	struct Nugget
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
	void _M_clear();
};

class NuggetInsertOverflowShim
{
public:
	void insert_overflow(ModuleInfo::Nugget *pos, const ModuleInfo::Nugget &x, const __false_type &tag, unsigned int fill_len, bool at_end);
	void clear();
};

void vector<ModuleInfo::Nugget, allocator<ModuleInfo::Nugget> >::_M_insert_overflow(
	ModuleInfo::Nugget *pos, const ModuleInfo::Nugget &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((NuggetInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}

void vector<ModuleInfo::Nugget, allocator<ModuleInfo::Nugget> >::_M_clear()
{
	((NuggetInsertOverflowShim *)this)->clear();
}
}
