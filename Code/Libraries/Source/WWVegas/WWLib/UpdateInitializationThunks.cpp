class WaterRenderObjClass
{
public:
	void enableWaterGrid(bool);
};

class WinInstanceData
{
public:
	void init();
};

class BoneFXUpdate
{
protected:
	void initTimes();
};

class DockUpdate
{
protected:
	void loadDockPositions();
};

class RailedTransportDockUpdate
{
protected:
	void unloadNext();
};

__declspec(naked) void WaterRenderObjClass::enableWaterGrid(bool)
{
	__asm {
		_emit 0E9h
		_emit 024h
		_emit 0ADh
		_emit 076h
		_emit 000h
	}
}

__declspec(naked) void WinInstanceData::init()
{
	__asm {
		_emit 0E9h
		_emit 084h
		_emit 079h
		_emit 047h
		_emit 000h
	}
}

__declspec(naked) void BoneFXUpdate::initTimes()
{
	__asm {
		_emit 0E9h
		_emit 0C6h
		_emit 08Dh
		_emit 025h
		_emit 000h
	}
}

__declspec(naked) void DockUpdate::loadDockPositions()
{
	__asm {
		_emit 0E9h
		_emit 006h
		_emit 0EBh
		_emit 02Bh
		_emit 000h
	}
}

__declspec(naked) void RailedTransportDockUpdate::unloadNext()
{
	__asm {
		_emit 0E9h
		_emit 07Ch
		_emit 023h
		_emit 02Ch
		_emit 000h
	}
}
