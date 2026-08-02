class Locomotor;
class LocomotorTemplate;

class LocomotorStore
{
public:
    Locomotor *newLocomotor(const LocomotorTemplate *) const;
};

class LocomotorStoreNewLocomotorShim
{
public:
    Locomotor *create(const LocomotorTemplate *tmpl) const;
};

Locomotor *LocomotorStore::newLocomotor(const LocomotorTemplate *tmpl) const
{
    return ((const LocomotorStoreNewLocomotorShim *)this)->create(tmpl);
}
