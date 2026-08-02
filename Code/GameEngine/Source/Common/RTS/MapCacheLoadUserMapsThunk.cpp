// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class MapCache
{
    bool loadUserMaps();
};

class MapCacheLoadUserMapsShim
{
public:
    bool load();
};

bool MapCache::loadUserMaps()
{
    return ((MapCacheLoadUserMapsShim *)this)->load();
}
