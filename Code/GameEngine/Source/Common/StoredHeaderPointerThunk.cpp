struct StoredHeaderPointerThunk
{
    unsigned char *pointer;

    unsigned char *payload() const;
};

unsigned char *StoredHeaderPointerThunk::payload() const
{
    return pointer + 12;
}
