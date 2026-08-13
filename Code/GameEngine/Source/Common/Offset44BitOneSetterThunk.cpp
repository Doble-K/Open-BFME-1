struct Offset44BitOneSetterThunk
{
    unsigned char padding[0x44];
    unsigned int flags;

    void set_bit_one();
};

void Offset44BitOneSetterThunk::set_bit_one()
{
    flags |= 2;
}
