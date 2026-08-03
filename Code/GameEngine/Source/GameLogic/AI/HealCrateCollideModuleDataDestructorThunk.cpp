// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HealCrateCollideModuleData dtor. SEH Buffer member pin body 0x887940.

class Buffer
{
public:
	~Buffer();
};

class HealCrateCollideModuleDataBase
{
public:
	virtual ~HealCrateCollideModuleDataBase() {}
private:
	unsigned char m_pad[0x40];
};

class __declspec(novtable) HealCrateCollideModuleData : public HealCrateCollideModuleDataBase
{
public:
	virtual ~HealCrateCollideModuleData();
private:
	Buffer m_buffer;
};

// ??1HealCrateCollideModuleData@@UAE@XZ
HealCrateCollideModuleData::~HealCrateCollideModuleData()
{
}
