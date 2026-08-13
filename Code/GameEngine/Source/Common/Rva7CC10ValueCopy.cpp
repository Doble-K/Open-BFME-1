class Rva7CC10ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *Rva7CC10ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
