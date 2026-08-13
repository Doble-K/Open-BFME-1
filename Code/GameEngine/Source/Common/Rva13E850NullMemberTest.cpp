class Rva13E850NullMemberTest {
public:
    bool empty() const;

private:
    void *m_first;
    void *m_value;
};

bool Rva13E850NullMemberTest::empty() const
{
    return m_value == 0;
}
