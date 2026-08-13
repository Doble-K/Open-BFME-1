class RvaA9C80ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaA9C80ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
