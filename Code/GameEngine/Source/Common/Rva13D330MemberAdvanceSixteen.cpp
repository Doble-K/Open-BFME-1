class Rva13D330MemberAdvanceSixteen {
public:
    unsigned char *advanced() const;

private:
    unsigned char *m_value;
};

unsigned char *Rva13D330MemberAdvanceSixteen::advanced() const
{
    return m_value + 16;
}
