// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Dict
{
    void releaseData();
};

class DictReleaseDataShim
{
public:
    void release();
};

void Dict::releaseData()
{
    ((DictReleaseDataShim *)this)->release();
}
