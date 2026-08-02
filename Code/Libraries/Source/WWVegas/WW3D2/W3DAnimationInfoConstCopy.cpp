// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class W3DAnimationInfo;

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

class W3DAnimationInfoConstCopyShim
{
public:
    static void *copy(void *first, void *last, void *result, const random_access_iterator_tag &, int *n);
};

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    return (Out)W3DAnimationInfoConstCopyShim::copy((void *)first, (void *)last, (void *)result, tag, (int *)n);
}

template W3DAnimationInfo *__copy<const W3DAnimationInfo *, W3DAnimationInfo *, int>(const W3DAnimationInfo *, const W3DAnimationInfo *, W3DAnimationInfo *, const random_access_iterator_tag &, int *);
}
