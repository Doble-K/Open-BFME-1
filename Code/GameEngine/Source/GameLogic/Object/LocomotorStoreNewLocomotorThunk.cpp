class Locomotor;
class LocomotorTemplate;

class Locomotor
{
    friend class LocomotorStore;

protected:
    Locomotor(const LocomotorTemplate *);

private:
    char m_storage[44];
};

class LocomotorStore
{
public:
    Locomotor *newLocomotor(const LocomotorTemplate *) const;
};

Locomotor *LocomotorStore::newLocomotor(const LocomotorTemplate *tmpl) const
{
    return new Locomotor(tmpl);
}
