// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift WeaponSet dtor __emit thunk to clean C++.
// Retail stores its own vtable at entry, loops over the four pointer slots at
// this+8 (virtual delete of each non-null element) under an SEH frame, then
// runs the inlined base dtor (base vtable store) on the unwind tail.

class WeaponSetElement
{
public:
    virtual ~WeaponSetElement();
};

class WeaponSetBase
{
public:
    virtual void weaponSetBaseVslot();
    ~WeaponSetBase() {}

private:
    unsigned int m_04;
};

class WeaponSet : public WeaponSetBase
{
public:
    virtual void weaponSetVslot();
    ~WeaponSet();

private:
    WeaponSetElement *m_slots[4];
};

// ??1WeaponSet@@QAE@XZ
WeaponSet::~WeaponSet()
{
    for (int i = 0; i < 4; ++i)
    {
        if (m_slots[i]) {
            delete m_slots[i];
        }
    }
}
