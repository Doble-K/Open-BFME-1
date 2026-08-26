// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor body through ILT 0x00025581. The
// explicit retail layout keeps this per-TU copy independent of Zero Hour's
// incompatible UpdateModule layout.

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

class DPEU_DeepBase
{
public:
    DPEU_DeepBase(Thing *, const ModuleData *);
    virtual ~DPEU_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class DPEU_Iface1 { public: virtual void slot(); };
class DPEU_Iface2 { public: virtual void slot(); };

class UpdateModule : public DPEU_DeepBase, public DPEU_Iface1, public DPEU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : DPEU_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class ExitInterface
{
public:
    virtual void exitObject();
};

class Coord3D
{
public:
    void zero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

private:
    float x;
    float y;
    float z;
};

class DefaultProductionExitUpdate : public UpdateModule, public ExitInterface
{
public:
    DefaultProductionExitUpdate(Thing *, const ModuleData *);

private:
    Coord3D m_rallyPoint;
    bool m_rallyPointExists;
};

// ??0DefaultProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
DefaultProductionExitUpdate::DefaultProductionExitUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_rallyPointExists = false;
    m_rallyPoint.zero();
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
