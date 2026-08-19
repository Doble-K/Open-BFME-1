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

class CreateModuleInterface
{
public:
	virtual void createModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class CreateModule : public BehaviorModule,
	public CreateModuleInterface,
	public ModuleInterface
{
public:
	CreateModule( Thing *thing, const ModuleData *moduleData );
};

class SpecialPowerCreate : public CreateModule
{
public:
	SpecialPowerCreate( Thing *thing, const ModuleData *moduleData );
};

SpecialPowerCreate::SpecialPowerCreate( Thing *thing, const ModuleData *moduleData )
	: CreateModule( thing, moduleData )
{
}
