class TerrainLogic
{
protected:
	void addWaypointLink(int, int);
};

class WaterTracksRenderSystem
{
public:
	void loadTracks();
};

class WaterTracksRenderSystemLoadTracksShim
{
public:
	void loadTracks();
};

void WaterTracksRenderSystem::loadTracks()
{
	((WaterTracksRenderSystemLoadTracksShim *)this)->loadTracks();
}
class TerrainLogicAddWaypointLinkShim
{
public:
    void add(int a, int b);
};

void TerrainLogic::addWaypointLink(int a, int b)
{
    ((TerrainLogicAddWaypointLinkShim *)this)->add(a, b);
}
