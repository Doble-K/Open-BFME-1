class RvaE6FF0SecondArgumentStore {
public:
    RvaE6FF0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaE6FF0SecondArgumentStore *RvaE6FF0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
