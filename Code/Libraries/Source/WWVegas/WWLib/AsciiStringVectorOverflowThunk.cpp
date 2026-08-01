class AsciiString
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

	__declspec(naked) void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(
		AsciiString *, const AsciiString &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 0ABh
			_emit 069h
			_emit 074h
			_emit 000h
		}
	}
}
