class Rva6EF10SecondArgumentStore {
public:
    Rva6EF10SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva6EF10SecondArgumentStore *Rva6EF10SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
