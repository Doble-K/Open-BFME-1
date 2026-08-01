// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString;

namespace _STL
{
	struct __false_type;

	template <class T>
	__declspec(naked) void __destroy_aux(T, T, const __false_type &)
	{
		__asm {
			_emit 0E9h
			_emit 07Ah
			_emit 059h
			_emit 06Eh
			_emit 000h
		}
	}

	template void __destroy_aux<AsciiString *>(AsciiString *, AsciiString *, const __false_type &);
}
