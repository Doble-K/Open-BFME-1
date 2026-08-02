class TerrainLogic;

class W3DRadar
{
protected:
    void buildTerrainTexture(TerrainLogic *);
};

class W3DRadarBuildTerrainTextureShim
{
public:
    void build(TerrainLogic *terrain);
};

void W3DRadar::buildTerrainTexture(TerrainLogic *terrain)
{
    ((W3DRadarBuildTerrainTextureShim *)this)->build(terrain);
}
