// cl: /DNDEBUG /MD /EHsc

class DamageInfo;

class Object
{
public:
	void onDie(DamageInfo *);
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	unsigned int m_moduleData;
	Object *m_object;
	unsigned int m_behaviorState;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *) = 0;
	virtual void attemptHealing(DamageInfo *) = 0;
};

class DamageInfo
{
	public:
	char m_inputPrefix[0x10];
	int m_damageType;
	char m_inputTail[0x3c];
	float m_actualDamageDealt;
	float m_actualDamageClipped;
	bool m_noEffect;
};

class InactiveBody : public BehaviorModule, public BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *);
	virtual void attemptHealing(DamageInfo *);

private:
	float m_health;
	bool m_dieCalled;
};

void InactiveBody::attemptDamage(DamageInfo *damageInfo)
{
	if (!damageInfo) {
		return;
	}

	if (damageInfo->m_damageType == 7) {
		attemptHealing(damageInfo);
		return;
	}

	damageInfo->m_actualDamageDealt = 0.0f;
	damageInfo->m_actualDamageClipped = 0.0f;
	damageInfo->m_noEffect = true;

	if (damageInfo->m_damageType == 8) {
		damageInfo->m_noEffect = false;
		if (!m_dieCalled) {
			m_object->onDie(damageInfo);
			m_dieCalled = true;
		}
	}
}
