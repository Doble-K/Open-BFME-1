// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MoneyCrateCollideModuleData dtor. SEH Buffer member pin body 0x887940.

class Buffer
{
public:
	~Buffer();
};

class MoneyCrateCollideModuleDataBase
{
public:
	virtual ~MoneyCrateCollideModuleDataBase() {}
private:
	unsigned char m_pad[0x40];
};

class __declspec(novtable) MoneyCrateCollideModuleData : public MoneyCrateCollideModuleDataBase
{
public:
	virtual ~MoneyCrateCollideModuleData();
private:
	Buffer m_buffer;
};

// ??1MoneyCrateCollideModuleData@@UAE@XZ
MoneyCrateCollideModuleData::~MoneyCrateCollideModuleData()
{
}
