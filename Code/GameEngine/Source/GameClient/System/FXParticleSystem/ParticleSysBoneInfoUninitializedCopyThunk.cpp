// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

struct ParticleSysBoneInfo;

namespace _STL
{
struct __false_type {};

template <class In, class Out>
Out __uninitialized_copy(In, In, Out, const __false_type &);

class ParticleSysBoneInfoUninitializedCopyShim
{
public:
	static void *copy(void *first, void *last, void *result, const __false_type &);
};

template <class In, class Out>
Out __uninitialized_copy(In first, In last, Out result, const __false_type &tag)
{
	return (Out)ParticleSysBoneInfoUninitializedCopyShim::copy((void *)first, (void *)last, (void *)result, tag);
}

template ParticleSysBoneInfo *__uninitialized_copy<const ParticleSysBoneInfo *, ParticleSysBoneInfo *>(const ParticleSysBoneInfo *, const ParticleSysBoneInfo *, ParticleSysBoneInfo *, const __false_type &);
}
