// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *thing, const ModuleData *moduleData );

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class DieModuleInterface
{
public:
	virtual void dieModuleInterfaceAnchor();
};

class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	DieModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData )
	{
	}
};

class CreateCrateDie : public DieModule
{
public:
	CreateCrateDie( Thing *thing, const ModuleData *moduleData );
};

CreateCrateDie::CreateCrateDie( Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}
