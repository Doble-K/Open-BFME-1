class Rva13D8B0NullTest
{
public:
    bool empty() const;

private:
    void *m_first;
    void *m_value;
};

bool Rva13D8B0NullTest::empty() const
{
    return m_value == 0;
}
