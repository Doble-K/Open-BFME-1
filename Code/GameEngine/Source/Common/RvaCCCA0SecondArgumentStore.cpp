class RvaCCCA0SecondArgumentStore {
public:
    RvaCCCA0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaCCCA0SecondArgumentStore *RvaCCCA0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
