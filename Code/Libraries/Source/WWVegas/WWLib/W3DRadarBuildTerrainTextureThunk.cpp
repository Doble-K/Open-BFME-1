class TerrainLogic;

class W3DRadar
{
protected:
	void buildTerrainTexture(TerrainLogic *);
};

__declspec(naked) void W3DRadar::buildTerrainTexture(TerrainLogic *)
{
	__asm {
		_emit 0E9h
		_emit 03Ch
		_emit 015h
		_emit 06Ah
		_emit 000h
	}
}
