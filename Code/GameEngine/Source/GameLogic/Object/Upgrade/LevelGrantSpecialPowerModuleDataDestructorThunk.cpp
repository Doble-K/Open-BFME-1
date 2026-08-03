// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LevelGrantSpecialPowerModuleData dtor. SEH member @+0x260 then base.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class LevelGrantSpecialPowerModuleDataBase
{
public:
	virtual ~LevelGrantSpecialPowerModuleDataBase();
private:
	unsigned char m_pad[0x25c];
};

class __declspec(novtable) LevelGrantSpecialPowerModuleData : public LevelGrantSpecialPowerModuleDataBase
{
public:
	virtual ~LevelGrantSpecialPowerModuleData();
private:
	Buffer m_buffer;
};

// ??1LevelGrantSpecialPowerModuleData@@UAE@XZ
LevelGrantSpecialPowerModuleData::~LevelGrantSpecialPowerModuleData()
{
}
