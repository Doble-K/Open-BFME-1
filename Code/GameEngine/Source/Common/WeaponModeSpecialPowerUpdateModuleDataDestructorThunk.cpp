// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponModeSpecialPowerUpdateModuleData dtor.
// SEH: Buffer @+0x1d0 then base dtor pin 0x1bbe4.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	virtual ~WeaponModeSpecialPowerUpdateModuleDataBase();
private:
	unsigned char m_pad[0x1cc];
};

class __declspec(novtable) WeaponModeSpecialPowerUpdateModuleData
	: public WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	virtual ~WeaponModeSpecialPowerUpdateModuleData();
private:
	Buffer m_buffer;
};

// ??1WeaponModeSpecialPowerUpdateModuleData@@UAE@XZ
WeaponModeSpecialPowerUpdateModuleData::~WeaponModeSpecialPowerUpdateModuleData()
{
}
