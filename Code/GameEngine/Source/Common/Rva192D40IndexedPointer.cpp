class Rva192D40IndexedPointer
{
public:
    unsigned char *at(unsigned int index);

private:
    unsigned char *m_base;
};

unsigned char *Rva192D40IndexedPointer::at(unsigned int index)
{
    return m_base + index * 140;
}
