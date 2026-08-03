// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WeaponBonusUpgrade module ctor via UpgradeModule multi-inheritance.

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
public:
	UpgradeModule( Thing *thing, const ModuleData *moduleData );
};

class WeaponBonusUpgrade : public UpgradeModule
{
public:
	WeaponBonusUpgrade( Thing *thing, const ModuleData *moduleData );
};

// ??0WeaponBonusUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
WeaponBonusUpgrade::WeaponBonusUpgrade(
	Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}