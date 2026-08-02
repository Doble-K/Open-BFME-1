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

class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	ActiveBody( Thing *thing, const ModuleData *moduleData );
};

class RespawnBody : public ActiveBody
{
public:
	RespawnBody( Thing *thing, const ModuleData *moduleData );
};

RespawnBody::RespawnBody( Thing *thing, const ModuleData *moduleData )
	: ActiveBody( thing, moduleData )
{
}
