// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	unsigned char m_pad[8];
};

class SpecialAbilityUpdateBaseInterface1
{
public:
	virtual void slot();
};

class SpecialAbilityUpdateBaseInterface2
{
public:
	virtual void slot();

private:
	unsigned char m_pad[0xC];
};

class SpecialAbilityUpdateObjectModule : public Gen_dtor_00113f20
{
};

class SpecialAbilityUpdateBehaviorModule : public SpecialAbilityUpdateObjectModule,
	public SpecialAbilityUpdateBaseInterface1
{
public:
	virtual ~SpecialAbilityUpdateBehaviorModule() {}
};

class SpecialAbilityUpdateUpdateModule : public SpecialAbilityUpdateBehaviorModule,
	public SpecialAbilityUpdateBaseInterface2
{
public:
	virtual ~SpecialAbilityUpdateUpdateModule() {}
};

class SpecialAbilityUpdateInterface
{
public:
	virtual void slot();
};

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

private:
	unsigned char m_pad[0x94];
};

class SpecialAbilityUpdate : public SpecialAbilityUpdateUpdateModule,
	public SpecialAbilityUpdateInterface
{
public:
	virtual ~SpecialAbilityUpdate();

private:
	void onExit(bool, bool);

	unsigned char m_pad[0x10];
	AudioEventRTS m_prepSoundLoop;
	_STL::list<int> m_specialObjectIDList;
};

// ??1SpecialAbilityUpdate@@UAE@XZ
SpecialAbilityUpdate::~SpecialAbilityUpdate()
{
	onExit(true, true);
}
