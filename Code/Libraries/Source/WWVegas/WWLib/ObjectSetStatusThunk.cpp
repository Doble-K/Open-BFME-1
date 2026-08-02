template <int Bits>
class BitFlags
{
};

class Object
{
public:
    void setStatus(BitFlags<45>, bool);
};

class ObjectSetStatusShim
{
public:
    void set(BitFlags<45> flags, bool value);
};

void Object::setStatus(BitFlags<45> flags, bool value)
{
    ((ObjectSetStatusShim *)this)->set(flags, value);
}
