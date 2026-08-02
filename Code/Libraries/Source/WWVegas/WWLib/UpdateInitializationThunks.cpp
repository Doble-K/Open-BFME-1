// DockUpdate::loadDockPositions was removed from this file. A 5-byte thunk row
// byte-verifies against any incremental-link entry, because every one is
// E9 xx xx xx xx and the displacement is a REL32 filled in from the target, so
// the name is never tested -- and following that thunk leads to the matched
// DockUpdate::update, which returns UpdateSleepTime where loadDockPositions
// returns void. A linker fold cannot span that.
//
// The other three stay: their bodies are unclaimed, so nothing contradicts them.
// See tools/audit_thunk_rows.py before adding another row here.
class WaterRenderObjClass
{
public:
	void enableWaterGrid(bool);
};

class BoneFXUpdate
{
protected:
	void initTimes();
};

class RailedTransportDockUpdate
{
protected:
	void unloadNext();
};

class WaterRenderObjClassEnableWaterGridShim
{
public:
	void enableWaterGrid(bool a0);
};

class BoneFXUpdateInitTimesShim
{
public:
	void initTimes();
};

class RailedTransportDockUpdateUnloadNextShim
{
public:
	void unloadNext();
};

void WaterRenderObjClass::enableWaterGrid(bool a0)
{
	((WaterRenderObjClassEnableWaterGridShim *)this)->enableWaterGrid(a0);
}

void BoneFXUpdate::initTimes()
{
	((BoneFXUpdateInitTimesShim *)this)->initTimes();
}

void RailedTransportDockUpdate::unloadNext()
{
	((RailedTransportDockUpdateUnloadNextShim *)this)->unloadNext();
}
