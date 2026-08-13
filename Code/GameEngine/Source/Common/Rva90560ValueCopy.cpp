class Rva90560ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *Rva90560ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
