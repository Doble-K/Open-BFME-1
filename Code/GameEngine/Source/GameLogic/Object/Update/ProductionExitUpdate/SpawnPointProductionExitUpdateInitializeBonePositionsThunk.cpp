class SpawnPointProductionExitUpdate
{
	void initializeBonePositions();
};

__declspec(naked) void SpawnPointProductionExitUpdate::initializeBonePositions()
{
	__asm {
		_emit 0E9h
		_emit 085h
		_emit 063h
		_emit 029h
		_emit 000h
	}
}
