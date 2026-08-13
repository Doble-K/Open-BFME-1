struct StoredFourByteHeaderPointerThunk
{
    unsigned char *pointer;

    unsigned char *payload() const;
};

unsigned char *StoredFourByteHeaderPointerThunk::payload() const
{
    return pointer + 4;
}
