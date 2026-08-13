class RvaE14A0ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaE14A0ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
