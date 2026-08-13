class Rva13E990BitTest
{
public:
    bool test(unsigned int bit) const;

private:
    unsigned int m_bits;
};

bool Rva13E990BitTest::test(unsigned int bit) const
{
    return (m_bits & (1U << (bit & 31))) != 0;
}
