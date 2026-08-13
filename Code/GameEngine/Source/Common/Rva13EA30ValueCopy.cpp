class Rva13EA30ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *Rva13EA30ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
