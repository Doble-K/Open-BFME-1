// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift SpawnUnitBehavior ctor __emit thunk to clean C++.
// Retail shape: grandbase ctor call with both args, interface-base vtable
// stores at +0x0C/+0x10, field inits (+0x18/+0x1C = -1, +0x14 = 0), vtable
// store for this class's own interface base at +0x20, then the four
// most-derived vtable stores and a byte copied from the object at this+4.
// /EHs- because retail has no unwind frame.

class Thing;
class ModuleData;

class SpawnUnitBehaviorGrandBase
{
public:
    SpawnUnitBehaviorGrandBase(Thing *, const ModuleData *);
    virtual ~SpawnUnitBehaviorGrandBase();

protected:
    unsigned int m_04;

private:
    unsigned char m_pad[4];
};

class SpawnUnitBehaviorIface1
{
public:
    virtual ~SpawnUnitBehaviorIface1();
};

class SpawnUnitBehaviorIface2
{
public:
    virtual ~SpawnUnitBehaviorIface2();
};

class SpawnUnitBehaviorIface3
{
public:
    virtual ~SpawnUnitBehaviorIface3();
};

class SpawnUnitBehaviorBase : public SpawnUnitBehaviorGrandBase, public SpawnUnitBehaviorIface1, public SpawnUnitBehaviorIface2
{
public:
    SpawnUnitBehaviorBase(Thing *t, const ModuleData *m)
        : SpawnUnitBehaviorGrandBase(t, m), m_14(0), m_18(-1), m_1C(-1) {}
    virtual ~SpawnUnitBehaviorBase();

private:
    unsigned int m_14;
    int m_18;
    int m_1C;
};

class SpawnUnitBehavior : public SpawnUnitBehaviorBase, public SpawnUnitBehaviorIface3
{
public:
    SpawnUnitBehavior(Thing *, const ModuleData *);

private:
    unsigned char m_24;
};

// ??0SpawnUnitBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
SpawnUnitBehavior::SpawnUnitBehavior(Thing *t, const ModuleData *m)
    : SpawnUnitBehaviorBase(t, m)
{
    m_24 = *((unsigned char *)m_04 + 0x1C);
}
