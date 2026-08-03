// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CivilianSpawnCollideModuleData dtor.
// Retail 67B SEH: destroy Buffer @+0x8, base vtbl store. Buffer pin 0x1A401.

class Buffer
{
public:
	~Buffer();
};

class CivilianSpawnCollideModuleDataBase
{
public:
	virtual ~CivilianSpawnCollideModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) CivilianSpawnCollideModuleData
	: public CivilianSpawnCollideModuleDataBase
{
public:
	virtual ~CivilianSpawnCollideModuleData();

private:
	Buffer m_buffer;
};

// ??1CivilianSpawnCollideModuleData@@UAE@XZ
CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData()
{
}
