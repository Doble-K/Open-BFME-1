// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class ObjectModule
{
public:
	virtual void objectModuleAnchor();

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();

private:
	unsigned int m_state;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpgradeModuleInterface,
	public ModuleInterface
{
public:
	UpgradeModule( Thing *, const ModuleData * );
};

class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();
};

class CostModifierUpgrade : public UpgradeModule, public UpgradeMux
{
public:
	CostModifierUpgrade( Thing *, const ModuleData * );

private:
	bool m_enabled;
};

CostModifierUpgrade::CostModifierUpgrade( Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData ),
	  m_enabled( true )
{
}
