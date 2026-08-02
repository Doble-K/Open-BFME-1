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
		: ObjectModule( thing, moduleData ),
		  m_deathType( 0 ),
		  m_isActive( false )
	{
	}

private:
	unsigned int m_deathType;
	bool m_isActive;
};

class SpecialPowerCompletionDie : public DieModule
{
public:
	SpecialPowerCompletionDie( Thing *, const ModuleData * );
};

SpecialPowerCompletionDie::SpecialPowerCompletionDie(
	Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}
