// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FireWeaponWhenDeadBehaviorModuleData dtor. SEH member@+0x8 pin 0x1B97D.

class UnpauseSpecialPowerUpgradeModuleDataMember
{
public:
	~UnpauseSpecialPowerUpgradeModuleDataMember();
};

class FireWeaponWhenDeadBehaviorModuleDataBase
{
public:
	virtual ~FireWeaponWhenDeadBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) FireWeaponWhenDeadBehaviorModuleData : public FireWeaponWhenDeadBehaviorModuleDataBase
{
public:
	virtual ~FireWeaponWhenDeadBehaviorModuleData();
private:
	UnpauseSpecialPowerUpgradeModuleDataMember m_member;
};

// ??1FireWeaponWhenDeadBehaviorModuleData@@UAE@XZ
FireWeaponWhenDeadBehaviorModuleData::~FireWeaponWhenDeadBehaviorModuleData()
{
}
