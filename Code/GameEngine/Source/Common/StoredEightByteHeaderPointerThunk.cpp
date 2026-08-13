struct StoredEightByteHeaderPointerThunk
{
    unsigned char *pointer;

    unsigned char *payload() const;
};

unsigned char *StoredEightByteHeaderPointerThunk::payload() const
{
    return pointer + 8;
}
