// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Radar
{
protected:
    void deleteListResources();
};

class RadarDeleteListResourcesShim
{
public:
    void clear();
};

void Radar::deleteListResources()
{
    ((RadarDeleteListResourcesShim *)this)->clear();
}
