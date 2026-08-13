class Rva6EEE0SecondArgumentStore {
public:
    Rva6EEE0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva6EEE0SecondArgumentStore *Rva6EEE0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
