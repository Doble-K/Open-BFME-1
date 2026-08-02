// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class W3DAnimationInfo;

namespace _STL
{
struct __false_type {};

template <class In, class Out>
Out __uninitialized_copy(In, In, Out, const __false_type &);

class W3DAnimationInfoUninitializedCopyShim
{
public:
	static void *copy(void *first, void *last, void *result, const __false_type &);
};

template <class In, class Out>
Out __uninitialized_copy(In first, In last, Out result, const __false_type &tag)
{
	return (Out)W3DAnimationInfoUninitializedCopyShim::copy((void *)first, (void *)last, (void *)result, tag);
}

template W3DAnimationInfo *__uninitialized_copy<const W3DAnimationInfo *, W3DAnimationInfo *>(const W3DAnimationInfo *, const W3DAnimationInfo *, W3DAnimationInfo *, const __false_type &);
}
