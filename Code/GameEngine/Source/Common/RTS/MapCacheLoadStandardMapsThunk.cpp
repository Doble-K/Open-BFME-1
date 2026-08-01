// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class MapCache
{
    void loadStandardMaps();
};

__declspec(naked) void MapCache::loadStandardMaps()
{
    __asm {
        _emit 0E9h
        _emit 0C0h
        _emit 0ADh
        _emit 041h
        _emit 000h
    }
}
