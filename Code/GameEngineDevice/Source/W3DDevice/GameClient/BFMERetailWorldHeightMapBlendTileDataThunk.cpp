// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

struct TBlendTileInfo;

class BFMERetailWorldHeightMap
{
public:
    void blendTileData(TBlendTileInfo *blend, int width);
};

class BFMERetailWorldHeightMapBlendTileDataShim
{
public:
    void blendTileData(TBlendTileInfo *, int);
};

void BFMERetailWorldHeightMap::blendTileData(TBlendTileInfo *blend, int width)
{
    ((BFMERetailWorldHeightMapBlendTileDataShim *)this)->blendTileData(blend, width);
}
