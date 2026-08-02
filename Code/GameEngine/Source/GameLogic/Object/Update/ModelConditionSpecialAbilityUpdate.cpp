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

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();

private:
	unsigned char m_data[12];
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class SpecialAbilityUpdate : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface,
	public ModuleInterface
{
public:
	SpecialAbilityUpdate( Thing *thing, const ModuleData *moduleData );
};

class ModelConditionSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	ModelConditionSpecialAbilityUpdate( Thing *thing, const ModuleData *moduleData );
};

ModelConditionSpecialAbilityUpdate::ModelConditionSpecialAbilityUpdate(
	Thing *thing, const ModuleData *moduleData )
	: SpecialAbilityUpdate( thing, moduleData )
{
}
