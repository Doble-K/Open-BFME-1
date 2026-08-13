struct PointerRangeSizeThunk
{
    int *begin;
    int *end;

    int size() const;
};

int PointerRangeSizeThunk::size() const
{
    return end - begin;
}
