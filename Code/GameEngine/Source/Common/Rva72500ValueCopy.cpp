class Rva72500ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *Rva72500ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
