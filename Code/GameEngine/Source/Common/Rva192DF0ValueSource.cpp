class Rva192DF0ValueSource
{
public:
    unsigned int *copy_value(unsigned int *output);

private:
    unsigned int *m_source;
};

unsigned int *Rva192DF0ValueSource::copy_value(unsigned int *output)
{
    *output = *m_source;
    return output;
}
