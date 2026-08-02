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

class WaterTracksRenderSystemLoadTracksShim
{
public:
	void loadTracks();
};

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

__declspec(naked) void FontLibrary::deleteAllFonts()
{
	__asm {
		_emit 0E9h
		_emit 0BFh
		_emit 017h
		_emit 06Fh
		_emit 000h
	}
}

__declspec(naked) void SimpleObjectIterator::makeEmpty()
{
	__asm {
		_emit 0E9h
		_emit 002h
		_emit 059h
		_emit 03Fh
		_emit 000h
	}
}
