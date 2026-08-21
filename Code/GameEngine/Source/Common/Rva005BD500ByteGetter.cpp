// Retail at 0x005BD500 returns the byte at this+0x1A8.
// The owning type and field semantics were not recovered.
struct Rva005BD500ByteGetter
{
    unsigned char m_pad[0x1A8];
    unsigned char m_value;

    unsigned char get_value();
};

unsigned char Rva005BD500ByteGetter::get_value()
{
    return m_value;
}
