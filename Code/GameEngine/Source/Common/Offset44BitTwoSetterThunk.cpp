struct Offset44BitTwoSetterThunk
{
    unsigned char padding[0x44];
    unsigned int flags;

    void set_bit_two();
};

void Offset44BitTwoSetterThunk::set_bit_two()
{
    flags |= 4;
}
