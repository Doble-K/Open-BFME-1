class Rva13D320MemberAdvanceSixteen {
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva13D320MemberAdvanceSixteen::advanced() const
{
    return m_value + 16;
}
