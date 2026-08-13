struct RvaB7F70Offset8ByteOneSetterThunk
{
    unsigned char padding[8];
    unsigned char enabled;

    void enable();
};

void RvaB7F70Offset8ByteOneSetterThunk::enable()
{
    enabled = 1;
}
