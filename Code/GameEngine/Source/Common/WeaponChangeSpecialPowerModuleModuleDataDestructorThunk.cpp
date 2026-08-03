// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponChangeSpecialPowerModuleModuleData dtor. 2x Buffer then base.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class WeaponChangeSpecialPowerModuleModuleDataBase
{
public:
	virtual ~WeaponChangeSpecialPowerModuleModuleDataBase();
private:
	unsigned char m_pad[0x218];
};

class __declspec(novtable) WeaponChangeSpecialPowerModuleModuleData : public WeaponChangeSpecialPowerModuleModuleDataBase
{
public:
	virtual ~WeaponChangeSpecialPowerModuleModuleData();
private:
	Buffer m_0;
	Buffer m_1;
};

// ??1WeaponChangeSpecialPowerModuleModuleData@@UAE@XZ
WeaponChangeSpecialPowerModuleModuleData::~WeaponChangeSpecialPowerModuleModuleData()
{
}
