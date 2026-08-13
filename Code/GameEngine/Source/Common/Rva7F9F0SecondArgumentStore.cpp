class Rva7F9F0SecondArgumentStore
{
public:
    Rva7F9F0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva7F9F0SecondArgumentStore *Rva7F9F0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
