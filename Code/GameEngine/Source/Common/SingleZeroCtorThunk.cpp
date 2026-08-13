struct SingleZeroCtorThunk
{
    unsigned long value;

    SingleZeroCtorThunk();
};

SingleZeroCtorThunk::SingleZeroCtorThunk() : value(0)
{
}
