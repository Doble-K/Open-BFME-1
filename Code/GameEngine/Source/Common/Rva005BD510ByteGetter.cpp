// Retail at 0x005BD510 loads the byte at this+0x1AA and returns.
// The owning type and field semantics were not recovered.
class Rva005BD510ByteGetter
{
public:
    unsigned char get() const;

private:
    unsigned char m_padding[0x1AA];
    unsigned char m_value;
};

unsigned char Rva005BD510ByteGetter::get() const
{
    return m_value;
}
