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

	__declspec(naked) void vector<PlayerTemplate, allocator<PlayerTemplate> >::_M_insert_overflow(
		PlayerTemplate *, const PlayerTemplate &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 05Dh
			_emit 03Ah
			_emit 00Bh
			_emit 000h
		}
	}
}
