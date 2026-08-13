class RvaE7160SecondArgumentStore {
public:
    RvaE7160SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaE7160SecondArgumentStore *RvaE7160SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
