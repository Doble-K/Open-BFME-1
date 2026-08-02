class TeamFactory
{
public:
    void clear();
};

class TeamFactoryClearShim
{
public:
    void run();
};

void TeamFactory::clear()
{
    ((TeamFactoryClearShim *)this)->run();
}
