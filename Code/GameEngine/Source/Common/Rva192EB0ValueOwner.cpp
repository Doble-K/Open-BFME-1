class Rva192EB0ValueOwner
{
public:
    unsigned int *copy_value(unsigned int *output);

private:
    unsigned int m_value;
};

unsigned int *Rva192EB0ValueOwner::copy_value(unsigned int *output)
{
    *output = m_value;
    return output;
}
