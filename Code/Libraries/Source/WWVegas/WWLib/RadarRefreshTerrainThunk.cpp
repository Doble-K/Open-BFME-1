class TerrainLogic;

class Radar
{
public:
	virtual void refreshTerrain(TerrainLogic *);
};

__declspec(naked) void Radar::refreshTerrain(TerrainLogic *)
{
	__asm {
		_emit 0E9h
		_emit 0AEh
		_emit 0F0h
		_emit 021h
		_emit 000h
	}
}
