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

__declspec(naked) void TerrainLogic::addWaypointLink(int, int)
{
	__asm {
		_emit 0E9h
		_emit 074h
		_emit 0D5h
		_emit 016h
		_emit 000h
	}
}
