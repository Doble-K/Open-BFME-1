// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class MapCache
{
    void writeCacheINI(bool);
};

class MapCacheWriteCacheINIShim
{
public:
    void write(bool user);
};

void MapCache::writeCacheINI(bool user)
{
    ((MapCacheWriteCacheINIShim *)this)->write(user);
}
