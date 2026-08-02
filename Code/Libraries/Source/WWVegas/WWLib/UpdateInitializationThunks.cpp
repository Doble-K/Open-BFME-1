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

class DockUpdateLoadDockPositionsShim
{
public:
	void loadDockPositions();
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

void DockUpdate::loadDockPositions()
{
	((DockUpdateLoadDockPositionsShim *)this)->loadDockPositions();
}

void RailedTransportDockUpdate::unloadNext()
{
	((RailedTransportDockUpdateUnloadNextShim *)this)->unloadNext();
}
