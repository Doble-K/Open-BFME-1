// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct ParticleSysBoneInfo;

namespace _STL
{
	struct __false_type;

	template <class In, class Out>
	__declspec(naked) Out __uninitialized_copy(In, In, Out, const __false_type &)
	{
		__asm {
			_emit 0E9h
			_emit 015h
			_emit 0CBh
			_emit 007h
			_emit 000h
		}
	}

	template ParticleSysBoneInfo *__uninitialized_copy<const ParticleSysBoneInfo *, ParticleSysBoneInfo *>(const ParticleSysBoneInfo *, const ParticleSysBoneInfo *, ParticleSysBoneInfo *, const __false_type &);
}
