class RvaCCCE0SecondArgumentStore {
public:
    RvaCCCE0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaCCCE0SecondArgumentStore *RvaCCCE0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
