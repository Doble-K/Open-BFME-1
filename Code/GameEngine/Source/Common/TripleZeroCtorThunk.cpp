struct TripleZeroCtorThunk
{
    unsigned long first;
    unsigned long second;
    unsigned long third;

    TripleZeroCtorThunk();
};

TripleZeroCtorThunk::TripleZeroCtorThunk() : first(0), second(0), third(0)
{
}
