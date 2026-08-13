unsigned long extractSecondByte(unsigned long value)
{
    return static_cast<unsigned char>(value >> 8);
}

unsigned long extractBit16(unsigned long value)
{
    return (value >> 16) & 1;
}
