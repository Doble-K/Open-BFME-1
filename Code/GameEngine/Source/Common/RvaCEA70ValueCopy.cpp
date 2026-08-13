class RvaCEA70ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaCEA70ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
