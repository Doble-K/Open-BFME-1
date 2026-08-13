class RvaCC980ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaCC980ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
