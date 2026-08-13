class Rva72510ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *Rva72510ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
