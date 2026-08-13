class Rva13D290PointerAssign {
public:
    Rva13D290PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

Rva13D290PointerAssign *Rva13D290PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}
