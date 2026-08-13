class Rva7FB20SecondArgumentStore
{
public:
    Rva7FB20SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva7FB20SecondArgumentStore *Rva7FB20SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
