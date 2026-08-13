class Rva13D5D0MemberAdvanceSixteen {
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva13D5D0MemberAdvanceSixteen::advanced() const
{
    return m_value + 16;
}
