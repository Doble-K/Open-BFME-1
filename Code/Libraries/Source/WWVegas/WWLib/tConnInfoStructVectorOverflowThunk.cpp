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

	__declspec(naked) void vector<tConnInfoStruct, allocator<tConnInfoStruct> >::_M_insert_overflow(
		tConnInfoStruct *, const tConnInfoStruct &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 0F5h
			_emit 0E3h
			_emit 05Eh
			_emit 000h
		}
	}
}
