class Rva13D540PointerAssign {
public:
    Rva13D540PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

Rva13D540PointerAssign *Rva13D540PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}
