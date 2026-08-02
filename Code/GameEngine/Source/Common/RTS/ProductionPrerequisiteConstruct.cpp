// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ProductionPrerequisite;

namespace _STL
{
template <class T, class U>
void _Construct(T *, const U &);

class ProductionPrerequisiteConstructShim
{
public:
    static void construct(ProductionPrerequisite *p, const ProductionPrerequisite &v);
};

template <class T, class U>
void _Construct(T *p, const U &v)
{
    ProductionPrerequisiteConstructShim::construct((ProductionPrerequisite *)p, *(const ProductionPrerequisite *)&v);
}

template void _Construct<ProductionPrerequisite, ProductionPrerequisite>(ProductionPrerequisite *, const ProductionPrerequisite &);
}
