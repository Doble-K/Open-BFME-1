// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString;

namespace _STL
{
	struct random_access_iterator_tag;

	template <class In, class Out, class Distance>
	__declspec(naked) Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *)
	{
		__asm {
			_emit 0E9h
			_emit 0C5h
			_emit 073h
			_emit 06Bh
			_emit 000h
		}
	}

	template AsciiString *__copy<AsciiString *, AsciiString *, int>(AsciiString *, AsciiString *, AsciiString *, const random_access_iterator_tag &, int *);
}
