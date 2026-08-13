class Rva87710ValueReset
{
public:
    unsigned int *reset();

private:
    unsigned int value;
};

unsigned int *Rva87710ValueReset::reset()
{
    value = 0;
    return &value;
}
