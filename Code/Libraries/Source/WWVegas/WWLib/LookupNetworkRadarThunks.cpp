class AsciiString
{
};

class CommandButton
{
};

class ConnectionManager
{
};

struct ICoord2D
{
};

class Radar
{
public:
	bool localPixelToRadar(ICoord2D const *, ICoord2D *);
};

class RadarLocalPixelToRadarShim
{
public:
	bool localPixelToRadar(ICoord2D const *, ICoord2D *);
};

bool Radar::localPixelToRadar(ICoord2D const *source, ICoord2D *destination)
{
	return ((RadarLocalPixelToRadarShim *)this)->localPixelToRadar(source, destination);
}

class DisconnectManager
{
protected:
	bool isPlayerVotedOut(int, ConnectionManager *);
};

__declspec(naked) bool DisconnectManager::isPlayerVotedOut(int, ConnectionManager *)
{
	__asm {
		_emit 0E9h
		_emit 04Bh
		_emit 0CFh
		_emit 064h
		_emit 000h
	}
}
