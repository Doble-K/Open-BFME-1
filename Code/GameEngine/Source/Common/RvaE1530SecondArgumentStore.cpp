class RvaE1530SecondArgumentStore {
public:
    RvaE1530SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaE1530SecondArgumentStore *RvaE1530SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
