// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ProductionPrerequisite;

namespace _STL
{
class ProductionPrerequisiteDestroyShim
{
public:
    static void destroy(ProductionPrerequisite *first, ProductionPrerequisite *last);
};

namespace
{
class LocalProductionPrerequisite
{
public:
    virtual ~LocalProductionPrerequisite();
private:
    unsigned char m_pad[0x18 - sizeof(void *)];
};

// ?LocalProductionPrerequisite::~LocalProductionPrerequisite present-unmatched
LocalProductionPrerequisite::~LocalProductionPrerequisite()
{
}
}

// ProductionPrerequisiteDestroyShim::destroy present-unmatched
// ?ProductionPrerequisiteDestroyShim::destroy present-unmatched
void ProductionPrerequisiteDestroyShim::destroy(ProductionPrerequisite *first, ProductionPrerequisite *last)
{
    LocalProductionPrerequisite *f = (LocalProductionPrerequisite *)first;
    LocalProductionPrerequisite *l = (LocalProductionPrerequisite *)last;
    for (; f != l; ++f)
        f->~LocalProductionPrerequisite();
}
}
