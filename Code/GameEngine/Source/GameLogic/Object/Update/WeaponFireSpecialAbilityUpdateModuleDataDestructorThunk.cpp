// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponFireSpecialAbilityUpdateModuleData dtor. SEH Buffer @+0x254 then base.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class WeaponFireSpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~WeaponFireSpecialAbilityUpdateModuleDataBase();
private:
	unsigned char m_pad[0x250];
};

class __declspec(novtable) WeaponFireSpecialAbilityUpdateModuleData : public WeaponFireSpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~WeaponFireSpecialAbilityUpdateModuleData();
private:
	Buffer m_buffer;
};

// ??1WeaponFireSpecialAbilityUpdateModuleData@@UAE@XZ
WeaponFireSpecialAbilityUpdateModuleData::~WeaponFireSpecialAbilityUpdateModuleData()
{
}
