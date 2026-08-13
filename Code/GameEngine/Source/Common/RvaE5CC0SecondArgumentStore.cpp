class RvaE5CC0SecondArgumentStore {
public:
    RvaE5CC0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaE5CC0SecondArgumentStore *RvaE5CC0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
