// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Module
{
public:
	virtual ~Module();

private:
	const void *m_moduleData;
};

class ObjectModule : public Module
{
public:
	virtual ~ObjectModule();

private:
	void *m_thing;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class CollideModuleInterface
{
public:
	virtual void collideModuleInterfaceAnchor() = 0;
};

class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	virtual ~CollideModule() {}
};

class Weapon
{
public:
	virtual ~Weapon();
};

class FireWeaponCollide : public CollideModule
{
public:
	virtual ~FireWeaponCollide();

private:
	Weapon *m_collideWeapon;
	bool m_everFired;
};

FireWeaponCollide::~FireWeaponCollide()
{
	delete m_collideWeapon;
}
