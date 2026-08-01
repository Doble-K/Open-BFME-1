class UnicodeString
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

	__declspec(naked) void vector<UnicodeString, allocator<UnicodeString> >::_M_insert_overflow(
		UnicodeString *, const UnicodeString &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 098h
			_emit 0BFh
			_emit 051h
			_emit 000h
		}
	}
}
