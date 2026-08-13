class Rva192E40PointerOwner
{
public:
    unsigned char *offset();

private:
    unsigned char *m_value;
};

unsigned char *Rva192E40PointerOwner::offset()
{
    return m_value + 16;
}
