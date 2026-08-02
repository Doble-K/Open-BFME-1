class TerrainLogic;

class Radar
{
public:
    virtual void refreshTerrain(TerrainLogic *);
};

class RadarRefreshTerrainShim
{
public:
    void run(TerrainLogic *terrain);
};

void Radar::refreshTerrain(TerrainLogic *terrain)
{
    ((RadarRefreshTerrainShim *)this)->run(terrain);
}
