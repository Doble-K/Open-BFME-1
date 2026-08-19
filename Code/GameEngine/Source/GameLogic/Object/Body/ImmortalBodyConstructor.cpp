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

class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class BodyModule : public BehaviorModule,
	public BodyModuleInterface,
	public ModuleInterface
{
public:
	BodyModule( Thing *thing, const ModuleData *moduleData );
};

class ImmortalBody : public BodyModule
{
public:
	ImmortalBody( Thing *thing, const ModuleData *moduleData );
};

ImmortalBody::ImmortalBody( Thing *thing, const ModuleData *moduleData )
	: BodyModule( thing, moduleData )
{
}
