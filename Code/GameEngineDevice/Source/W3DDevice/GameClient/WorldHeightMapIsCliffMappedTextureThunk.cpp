// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class WorldHeightMap
{
public:
    bool isCliffMappedTexture(int x, int y);
};

class WorldHeightMapIsCliffMappedTextureShim
{
public:
    bool isCliffMappedTexture(int, int);
};

bool WorldHeightMap::isCliffMappedTexture(int x, int y)
{
    return ((WorldHeightMapIsCliffMappedTextureShim *)this)->isCliffMappedTexture(x, y);
}
