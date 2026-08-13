struct Rva87350Offset4Setter
{
    unsigned char unused[4];
    unsigned int value;

    void set_value(unsigned int new_value);
};

void Rva87350Offset4Setter::set_value(unsigned int new_value)
{
    value = new_value;
}
