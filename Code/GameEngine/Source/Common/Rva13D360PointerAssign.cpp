class Rva13D360PointerAssign {
public:
    Rva13D360PointerAssign *assign(const unsigned int *value);

private:
    unsigned int m_value;
};

Rva13D360PointerAssign *Rva13D360PointerAssign::assign(const unsigned int *value)
{
    m_value = *value;
    return this;
}
