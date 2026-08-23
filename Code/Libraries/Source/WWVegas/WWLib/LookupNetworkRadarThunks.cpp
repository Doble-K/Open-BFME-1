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
