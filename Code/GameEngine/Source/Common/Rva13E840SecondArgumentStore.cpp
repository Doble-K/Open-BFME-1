class Rva13E840SecondArgumentStore {
public:
    Rva13E840SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva13E840SecondArgumentStore *Rva13E840SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
