class RvaE6F30ValueCopy {
public:
    unsigned int *copy(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *RvaE6F30ValueCopy::copy(unsigned int *output)
{
    *output = m_value;
    return output;
}
