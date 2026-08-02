// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ProductionPrerequisite;

namespace _STL
{
struct random_access_iterator_tag {};

template <class In, class Out, class Distance>
Out __copy(In, In, Out, const random_access_iterator_tag &, Distance *);

class ProductionPrerequisiteCopyShim
{
public:
    static ProductionPrerequisite *copy(ProductionPrerequisite *first, ProductionPrerequisite *last, ProductionPrerequisite *result, const random_access_iterator_tag &, int *n);
};

template <class In, class Out, class Distance>
Out __copy(In first, In last, Out result, const random_access_iterator_tag &tag, Distance *n)
{
    return (Out)ProductionPrerequisiteCopyShim::copy((ProductionPrerequisite *)first, (ProductionPrerequisite *)last, (ProductionPrerequisite *)result, tag, (int *)n);
}

template ProductionPrerequisite *__copy<ProductionPrerequisite *, ProductionPrerequisite *, int>(ProductionPrerequisite *, ProductionPrerequisite *, ProductionPrerequisite *, const random_access_iterator_tag &, int *);
}
