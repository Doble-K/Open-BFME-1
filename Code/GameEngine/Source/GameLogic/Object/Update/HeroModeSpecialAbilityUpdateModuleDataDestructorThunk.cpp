// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HeroModeSpecialAbilityUpdateModuleData dtor. SEH Buffer @+0x254 then base.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class HeroModeSpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~HeroModeSpecialAbilityUpdateModuleDataBase();
private:
	unsigned char m_pad[0x250];
};

class __declspec(novtable) HeroModeSpecialAbilityUpdateModuleData : public HeroModeSpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~HeroModeSpecialAbilityUpdateModuleData();
private:
	Buffer m_buffer;
};

// ??1HeroModeSpecialAbilityUpdateModuleData@@UAE@XZ
HeroModeSpecialAbilityUpdateModuleData::~HeroModeSpecialAbilityUpdateModuleData()
{
}
