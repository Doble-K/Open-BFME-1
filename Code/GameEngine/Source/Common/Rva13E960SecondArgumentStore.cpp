class Rva13E960SecondArgumentStore {
public:
    Rva13E960SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva13E960SecondArgumentStore *Rva13E960SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
