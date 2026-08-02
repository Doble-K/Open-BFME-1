class TerrainTracksRenderObjClassSystem
{
public:
	void shutdown();
};

class WaterTracksRenderSystem
{
public:
	void shutdown();
};

class TerrainTracksShutdownShim
{
public:
	void shutdown();
};

class WaterTracksShutdownShim
{
public:
	void shutdown();
};

void TerrainTracksRenderObjClassSystem::shutdown()
{
	((TerrainTracksShutdownShim *)this)->shutdown();
}

void WaterTracksRenderSystem::shutdown()
{
	((WaterTracksShutdownShim *)this)->shutdown();
}
