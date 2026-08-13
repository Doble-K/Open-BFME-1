class RvaA8EC0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaA8EC0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
