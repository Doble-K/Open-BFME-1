class Rva9ED80SecondArgumentStore
{
public:
    Rva9ED80SecondArgumentStore *store(unsigned int ignored, unsigned int value);

private:
    unsigned int m_value;
};

Rva9ED80SecondArgumentStore *Rva9ED80SecondArgumentStore::store(unsigned int, unsigned int value)
{
    m_value = value;
    return this;
}
