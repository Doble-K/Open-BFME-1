// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: MapObject::setWaypointName
// Retail: Dict global setAsciiString(name) then assign result into this+0x24.

class AsciiString
{
public:
	unsigned int m_data;
};

class Dict
{
public:
	AsciiString *setAsciiString(AsciiString name);
};

extern Dict g_theWaypointNameDict;

class AsciiStringField
{
public:
	void set(AsciiString *src);
};

class MapObject
{
public:
	void setWaypointName(AsciiString name);

private:
	char m_pad[0x24];
	AsciiStringField m_name;
};

// ?setWaypointName@MapObject@@QAEXVAsciiString@@@Z
void MapObject::setWaypointName(AsciiString name)
{
	AsciiString *result = g_theWaypointNameDict.setAsciiString(name);
	m_name.set(result);
}
