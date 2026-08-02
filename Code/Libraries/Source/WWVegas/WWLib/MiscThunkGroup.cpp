class TerrainLogic
{
protected:
	void addWaypointLink(int, int);
};

class FontLibrary
{
protected:
	void deleteAllFonts();
};

class WaterTracksRenderSystem
{
public:
	void loadTracks();
};

class SimpleObjectIterator
{
public:
	void makeEmpty();
};

class SimpleObjectIteratorMakeEmptyShim
{
public:
	void makeEmpty();
};

void SimpleObjectIterator::makeEmpty()
{
	((SimpleObjectIteratorMakeEmptyShim *)this)->makeEmpty();
}

class WaterTracksRenderSystemLoadTracksShim
{
public:
	void loadTracks();
};

class FontLibraryDeleteAllFontsShim
{
public:
	void deleteAllFonts();
};

void FontLibrary::deleteAllFonts()
{
	((FontLibraryDeleteAllFontsShim *)this)->deleteAllFonts();
}

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
