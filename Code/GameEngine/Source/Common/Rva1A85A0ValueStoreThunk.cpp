struct Rva1A85A0ValueStoreThunk
{
    unsigned int value;

    unsigned int *store(unsigned int *destination);
};

unsigned int *Rva1A85A0ValueStoreThunk::store(unsigned int *destination)
{
    *destination = value;
    return destination;
}
