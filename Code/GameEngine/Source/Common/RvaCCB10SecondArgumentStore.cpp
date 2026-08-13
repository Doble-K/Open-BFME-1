class RvaCCB10SecondArgumentStore {
public:
    RvaCCB10SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

RvaCCB10SecondArgumentStore *RvaCCB10SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
