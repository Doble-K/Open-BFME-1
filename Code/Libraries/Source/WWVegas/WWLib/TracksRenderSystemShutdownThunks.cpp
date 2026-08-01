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

__declspec(naked) void TerrainTracksRenderObjClassSystem::shutdown()
{
	__asm {
		_emit 0E9h
		_emit 004h
		_emit 027h
		_emit 070h
		_emit 000h
	}
}

__declspec(naked) void WaterTracksRenderSystem::shutdown()
{
	__asm {
		_emit 0E9h
		_emit 090h
		_emit 0ABh
		_emit 077h
		_emit 000h
	}
}
