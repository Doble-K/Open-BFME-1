struct Offset4DA8WordGetterThunk
{
    unsigned char padding[0x4DA8];
    unsigned long value;

    unsigned long getValue() const;
};

unsigned long Offset4DA8WordGetterThunk::getValue() const
{
    return value;
}
