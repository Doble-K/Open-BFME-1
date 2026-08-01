struct EvaSideSounds
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

	__declspec(naked) void vector<EvaSideSounds, allocator<EvaSideSounds> >::_M_insert_overflow(
		EvaSideSounds *, const EvaSideSounds &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 07Bh
			_emit 05Ch
			_emit 025h
			_emit 000h
		}
	}
}
