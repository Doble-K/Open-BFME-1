// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's PoisonedBehavior allocation reaches this per-TU constructor
// through ILT 0x00041547. Its DamageModuleInterface base makes this body longer
// than the independently emitted constructor already held elsewhere.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_DUMMY };
enum DeathType { DEATH_POISONED = 5 };

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    void *m_p4;
    Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };
class DamageModuleInterface
{
public:
    virtual void onDamage();
    virtual void onHealing();
    virtual void onBodyDamageStateChange();
};

class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1C(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1C;
};

class PoisonedBehavior : public UpdateModule, public DamageModuleInterface
{
public:
    PoisonedBehavior(Thing *, const ModuleData *);

private:
    unsigned int m_poisonDamageFrame;
    unsigned int m_poisonOverallStopFrame;
    float m_poisonDamageAmount;
    DeathType m_deathType;
};

// ??0PoisonedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
PoisonedBehavior::PoisonedBehavior(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_poisonDamageFrame(0),
      m_poisonOverallStopFrame(0), m_poisonDamageAmount(0.0f),
      m_deathType(DEATH_POISONED)
{
    setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
}
