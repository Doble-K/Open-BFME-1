// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

namespace ProductionPrerequisite
{
struct PrereqUnitRec;
}

namespace _STL
{
template <class T, class U>
void _Construct(T *, const U &);

class PrereqUnitRecConstructShim
{
public:
    static void construct(ProductionPrerequisite::PrereqUnitRec *p, const ProductionPrerequisite::PrereqUnitRec &v);
};

template <class T, class U>
void _Construct(T *p, const U &v)
{
    PrereqUnitRecConstructShim::construct((ProductionPrerequisite::PrereqUnitRec *)p, *(const ProductionPrerequisite::PrereqUnitRec *)&v);
}

template void _Construct<ProductionPrerequisite::PrereqUnitRec, ProductionPrerequisite::PrereqUnitRec>(ProductionPrerequisite::PrereqUnitRec *, const ProductionPrerequisite::PrereqUnitRec &);
}
