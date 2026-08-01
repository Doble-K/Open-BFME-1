// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class MapCache
{
    bool loadUserMaps();
};

__declspec(naked) bool MapCache::loadUserMaps()
{
    __asm {
        _emit 0E9h
        _emit 0CAh
        _emit 0E7h
        _emit 042h
        _emit 000h
    }
}
