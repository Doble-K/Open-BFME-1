class Rva192E60PointerOwner
{
public:
    unsigned char *offset();

private:
    unsigned char *m_value;
};

unsigned char *Rva192E60PointerOwner::offset()
{
    return m_value + 16;
}
