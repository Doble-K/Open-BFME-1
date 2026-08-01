// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct ParticleSysBoneInfo;

namespace _STL
{
	struct random_access_iterator_tag;

	template <class In, class Out, class Distance>
	__declspec(naked) Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *)
	{
		__asm {
			_emit 0E9h
			_emit 024h
			_emit 0E3h
			_emit 006h
			_emit 000h
		}
	}

	template ParticleSysBoneInfo *__copy<const ParticleSysBoneInfo *, ParticleSysBoneInfo *, int>(const ParticleSysBoneInfo *, const ParticleSysBoneInfo *, ParticleSysBoneInfo *, const random_access_iterator_tag &, int *);
}
