class RvaBED50ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaBED50ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
