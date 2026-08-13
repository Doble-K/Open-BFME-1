class Rva92C20SecondArgumentStore
{
public:
    Rva92C20SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva92C20SecondArgumentStore *Rva92C20SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
