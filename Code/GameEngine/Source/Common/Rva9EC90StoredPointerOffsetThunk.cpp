struct Rva9EC90StoredPointerOffsetThunk
{
    char *value;

    char *offsetValue() const;
};

char *Rva9EC90StoredPointerOffsetThunk::offsetValue() const
{
    return value + 8;
}
