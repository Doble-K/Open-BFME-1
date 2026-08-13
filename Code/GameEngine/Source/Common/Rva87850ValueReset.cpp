class Rva87850ValueReset
{
public:
    unsigned int *reset();

private:
    unsigned int value;
};

unsigned int *Rva87850ValueReset::reset()
{
    value = 0;
    return &value;
}
