class RvaE72B0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaE72B0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
