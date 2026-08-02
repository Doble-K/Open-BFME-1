// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule( Thing *, const ModuleData * );

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
};

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	UpdateModule( Thing *thing, const ModuleData *moduleData )
		: ObjectModule( thing, moduleData )
	{
	}
};

class RunOffMapBehavior : public UpdateModule
{
public:
	RunOffMapBehavior( Thing *, const ModuleData * );
};

RunOffMapBehavior::RunOffMapBehavior( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
}
