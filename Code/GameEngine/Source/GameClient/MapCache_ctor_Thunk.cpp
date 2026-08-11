// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ lift of the retail MapCache constructor.

#include <map>
#include <set>

typedef int Bool;

class AsciiString
{
public:
	AsciiString();
	~AsciiString();
	bool operator<(const AsciiString &other) const;

private:
	char *m_data;
};

struct MapMetaData
{
	unsigned char m_data[252];
};

class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
	MapCache();

private:
	std::map<AsciiString, Bool> m_seen;
	std::set<AsciiString> m_allowedMaps;
};

MapCache::MapCache()
{
}
