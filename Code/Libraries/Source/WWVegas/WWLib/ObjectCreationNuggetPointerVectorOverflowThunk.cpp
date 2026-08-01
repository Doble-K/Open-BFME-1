class ObjectCreationNugget;

namespace _STL {

struct __true_type
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
	void _M_insert_overflow(Type *, const Type &, const __true_type &, unsigned int, bool);
};

__declspec(naked) void vector<ObjectCreationNugget *, allocator<ObjectCreationNugget *> >::_M_insert_overflow(
	ObjectCreationNugget **, ObjectCreationNugget * const &, const __true_type &, unsigned int, bool)
{
	__asm {
		_emit 0E9h
		_emit 003h
		_emit 0BEh
		_emit 01Ah
		_emit 000h
	}
}

}
