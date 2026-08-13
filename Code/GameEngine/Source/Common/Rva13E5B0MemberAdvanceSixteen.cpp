class Rva13E5B0MemberAdvanceSixteen
{
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva13E5B0MemberAdvanceSixteen::advanced() const
{
    return m_value + 16;
}
