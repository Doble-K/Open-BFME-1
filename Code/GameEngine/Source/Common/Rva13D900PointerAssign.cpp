class Rva13D900PointerAssign
{
public:
    Rva13D900PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

Rva13D900PointerAssign *Rva13D900PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}
