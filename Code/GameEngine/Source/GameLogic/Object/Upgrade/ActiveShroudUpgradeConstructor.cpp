// cl: /DNDEBUG /MD /EHsc

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

class ActiveShroudUpgrade : public UpgradeModule
{
public:
	ActiveShroudUpgrade( Thing *thing, const ModuleData *moduleData );
};

ActiveShroudUpgrade::ActiveShroudUpgrade( Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}
