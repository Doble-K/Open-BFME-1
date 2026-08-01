// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ThingTemplate;
class AsciiString;

namespace _STL
{
	template <class First, class Second>
	struct pair
	{
	};

	template <class Pair>
	struct _Select1st
	{
	};

	template <class Type>
	struct less
	{
	};

	template <class Type>
	class allocator
	{
	};

	template <class Key, class Value, class Select, class Compare, class Allocator>
	class _Rb_tree
	{
	public:
		~_Rb_tree();
	};

	__declspec(naked) _Rb_tree<ThingTemplate const *, pair<ThingTemplate const * const, int>, _Select1st<pair<ThingTemplate const * const, int> >, less<ThingTemplate const *>, allocator<pair<ThingTemplate const * const, int> > >::~_Rb_tree()
	{
		__asm {
			_emit 0E9h
			_emit 01Eh
			_emit 0C0h
			_emit 00Ah
			_emit 000h
		}
	}

	__declspec(naked) _Rb_tree<AsciiString, pair<AsciiString const, bool>, _Select1st<pair<AsciiString const, bool> >, less<AsciiString>, allocator<pair<AsciiString const, bool> > >::~_Rb_tree()
	{
		__asm {
			_emit 0E9h
			_emit 074h
			_emit 03Fh
			_emit 006h
			_emit 000h
		}
	}
}
