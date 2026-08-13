class Rva13E710SecondArgumentStore {
public:
    Rva13E710SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva13E710SecondArgumentStore *Rva13E710SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
