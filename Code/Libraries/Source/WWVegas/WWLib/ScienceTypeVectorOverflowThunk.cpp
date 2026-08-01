// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

enum ScienceType
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

	__declspec(naked) void vector<ScienceType, allocator<ScienceType> >::_M_insert_overflow(ScienceType *, ScienceType const &, const __false_type &, unsigned int, bool)
	{
		__asm {
			_emit 0E9h
			_emit 073h
			_emit 090h
			_emit 009h
			_emit 000h
		}
	}
}
