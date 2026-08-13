class RvaBED60SecondArgumentStore {
public:
    RvaBED60SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaBED60SecondArgumentStore *RvaBED60SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
