class RvaA3600ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaA3600ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
