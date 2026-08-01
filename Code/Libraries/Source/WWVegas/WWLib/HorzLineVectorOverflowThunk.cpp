struct HorzLine
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

	__declspec(naked) void vector<HorzLine, allocator<HorzLine> >::_M_insert_overflow(
		HorzLine *, const HorzLine &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 0B9h
			_emit 010h
			_emit 005h
			_emit 000h
		}
	}
}
