class Rva13A430SignedByte
{
public:
    int value() const;

private:
    unsigned char m_prefix[0x496];
    signed char m_value;
};

int Rva13A430SignedByte::value() const
{
    return m_value;
}
