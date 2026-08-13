class Rva1A6CF0SecondArgumentStore
{
public:
    Rva1A6CF0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva1A6CF0SecondArgumentStore *Rva1A6CF0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
