// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

namespace _STL
{
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

	__declspec(naked) void vector<unsigned short, allocator<unsigned short> >::_M_insert_overflow(unsigned short *, unsigned short const &, const __true_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 07Dh
			_emit 09Dh
			_emit 03Bh
			_emit 000h
		}
	}
}
