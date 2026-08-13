class RvaCCCD0SecondArgumentStore {
public:
    RvaCCCD0SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaCCCD0SecondArgumentStore *RvaCCCD0SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
