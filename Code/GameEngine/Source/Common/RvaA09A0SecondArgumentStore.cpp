class RvaA09A0SecondArgumentStore {
public:
    RvaA09A0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaA09A0SecondArgumentStore *RvaA09A0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
