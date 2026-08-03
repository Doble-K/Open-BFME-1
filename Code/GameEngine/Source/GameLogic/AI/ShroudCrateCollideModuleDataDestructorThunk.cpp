// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ShroudCrateCollideModuleData dtor. SEH Buffer member pin body 0x887940.

class Buffer
{
public:
	~Buffer();
};

class ShroudCrateCollideModuleDataBase
{
public:
	virtual ~ShroudCrateCollideModuleDataBase() {}
private:
	unsigned char m_pad[0x40];
};

class __declspec(novtable) ShroudCrateCollideModuleData : public ShroudCrateCollideModuleDataBase
{
public:
	virtual ~ShroudCrateCollideModuleData();
private:
	Buffer m_buffer;
};

// ??1ShroudCrateCollideModuleData@@UAE@XZ
ShroudCrateCollideModuleData::~ShroudCrateCollideModuleData()
{
}
