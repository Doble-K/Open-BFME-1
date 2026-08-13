class Rva13DD30ValueStore
{
public:
    Rva13DD30ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

Rva13DD30ValueStore *Rva13DD30ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}
