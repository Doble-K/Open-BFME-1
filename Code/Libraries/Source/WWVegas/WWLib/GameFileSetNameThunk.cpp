class GameFileClass
{
public:
    virtual const char *Set_Name(const char *);
};

class GameFileSetNameShim
{
public:
    const char *set(const char *name);
};

const char *GameFileClass::Set_Name(const char *name)
{
    return ((GameFileSetNameShim *)this)->set(name);
}
