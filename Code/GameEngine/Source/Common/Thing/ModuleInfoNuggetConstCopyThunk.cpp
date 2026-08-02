// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ModuleInfo
{
public:
    struct Nugget;
};

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

class ModuleInfoNuggetConstCopyShim
{
public:
    static void *copy(void *first, void *last, void *result, const random_access_iterator_tag &, int *n);
};

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    return (Out)ModuleInfoNuggetConstCopyShim::copy((void *)first, (void *)last, (void *)result, tag, (int *)n);
}

template ModuleInfo::Nugget *__copy<const ModuleInfo::Nugget *, ModuleInfo::Nugget *, int>(const ModuleInfo::Nugget *, const ModuleInfo::Nugget *, ModuleInfo::Nugget *, const random_access_iterator_tag &, int *);
}
