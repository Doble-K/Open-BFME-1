struct DoubleZeroCtorThunk
{
    unsigned long first;
    unsigned long second;

    DoubleZeroCtorThunk();
};

DoubleZeroCtorThunk::DoubleZeroCtorThunk() : first(0), second(0)
{
}
