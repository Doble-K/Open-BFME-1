class Rva13E900SecondArgumentStore {
public:
    Rva13E900SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva13E900SecondArgumentStore *Rva13E900SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
