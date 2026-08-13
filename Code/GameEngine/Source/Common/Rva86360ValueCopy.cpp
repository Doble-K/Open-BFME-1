class Rva86360ValueCopy
{
public:
    unsigned int *copy(unsigned int *source);

private:
    unsigned int value;
};

unsigned int *Rva86360ValueCopy::copy(unsigned int *source)
{
    value = *source;
    return &value;
}
