class WeaponTemplateSet
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

	__declspec(naked) void vector<WeaponTemplateSet, allocator<WeaponTemplateSet> >::_M_insert_overflow(
		WeaponTemplateSet *, const WeaponTemplateSet &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 02Ch
			_emit 017h
			_emit 02Dh
			_emit 000h
		}
	}
}
