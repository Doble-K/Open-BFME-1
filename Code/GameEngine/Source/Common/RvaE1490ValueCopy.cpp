class RvaE1490ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaE1490ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
