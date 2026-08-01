// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class W3DAnimationInfo;

namespace _STL
{
	struct random_access_iterator_tag;

	template <class In, class Out, class Distance>
	__declspec(naked) Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *)
	{
		__asm {
			_emit 0E9h
			_emit 0C8h
			_emit 0CAh
			_emit 05Eh
			_emit 000h
		}
	}

	template W3DAnimationInfo *__copy<W3DAnimationInfo *, W3DAnimationInfo *, int>(W3DAnimationInfo *, W3DAnimationInfo *, W3DAnimationInfo *, const random_access_iterator_tag &, int *);
}
