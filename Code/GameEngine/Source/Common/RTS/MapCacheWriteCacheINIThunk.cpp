// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class MapCache
{
    void writeCacheINI(bool);
};

__declspec(naked) void MapCache::writeCacheINI(bool)
{
    __asm {
        _emit 0E9h
        _emit 007h
        _emit 06Eh
        _emit 044h
        _emit 000h
    }
}
