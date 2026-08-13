struct RvaA7380PointerRangeSizeThunk
{
    int *begin;
    int *unused;
    int *end;

    int size() const;
};

int RvaA7380PointerRangeSizeThunk::size() const
{
    return end - begin;
}
