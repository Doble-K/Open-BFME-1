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

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
};

class AIUpdateInterface : public ObjectModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface,
	public ModuleInterface,
	public AICommandInterface
{
public:
	AIUpdateInterface( Thing *, const ModuleData * );
};

class WanderAIUpdate : public AIUpdateInterface
{
public:
	WanderAIUpdate( Thing *, const ModuleData * );
};

WanderAIUpdate::WanderAIUpdate( Thing *thing, const ModuleData *moduleData )
	: AIUpdateInterface( thing, moduleData )
{
}
