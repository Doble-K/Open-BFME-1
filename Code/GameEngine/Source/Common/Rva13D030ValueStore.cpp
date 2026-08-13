class Rva13D030ValueStore {
public:
    Rva13D030ValueStore *store(unsigned int value);

private:
    unsigned int m_value;
};

Rva13D030ValueStore *Rva13D030ValueStore::store(unsigned int value)
{
    m_value = value;
    return this;
}
