// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

enum ScienceType
{
	SCIENCE_INVALID = -1
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

class ScienceTypeInsertOverflowShim
{
public:
	void insert_overflow(ScienceType *pos, const ScienceType &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<ScienceType, allocator<ScienceType> >::_M_insert_overflow(
	ScienceType *pos, const ScienceType &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((ScienceTypeInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
