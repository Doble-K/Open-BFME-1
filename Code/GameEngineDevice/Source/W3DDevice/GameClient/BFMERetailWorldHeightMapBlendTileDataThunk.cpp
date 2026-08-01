// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct TBlendTileInfo;

class BFMERetailWorldHeightMap
{
public:
    void blendTileData(TBlendTileInfo *blend, int width);
};

__declspec(naked) void BFMERetailWorldHeightMap::blendTileData(TBlendTileInfo *, int)
{
    __asm {
        _emit 0E9h
        _emit 044h
        _emit 03Ah
        _emit 073h
        _emit 000h
    }
}
