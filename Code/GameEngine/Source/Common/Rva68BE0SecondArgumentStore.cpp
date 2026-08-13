class Rva68BE0SecondArgumentStore
{
public:
    Rva68BE0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva68BE0SecondArgumentStore *Rva68BE0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
