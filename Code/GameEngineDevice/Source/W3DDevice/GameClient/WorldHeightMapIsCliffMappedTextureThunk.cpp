// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class WorldHeightMap
{
public:
    bool isCliffMappedTexture(int x, int y);
};

__declspec(naked) bool WorldHeightMap::isCliffMappedTexture(int, int)
{
    __asm {
        _emit 0E9h
        _emit 017h
        _emit 062h
        _emit 070h
        _emit 000h
    }
}
