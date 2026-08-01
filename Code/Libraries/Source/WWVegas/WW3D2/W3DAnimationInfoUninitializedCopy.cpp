// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class W3DAnimationInfo;

namespace _STL
{
	struct __false_type;

	template <class In, class Out>
	__declspec(naked) Out __uninitialized_copy(In, In, Out, const __false_type &)
	{
		__asm {
			_emit 0E9h
			_emit 044h
			_emit 0D0h
			_emit 038h
			_emit 000h
		}
	}

	template W3DAnimationInfo *__uninitialized_copy<const W3DAnimationInfo *, W3DAnimationInfo *>(const W3DAnimationInfo *, const W3DAnimationInfo *, W3DAnimationInfo *, const __false_type &);
}
