struct Rva1A94C0TripleZeroThunk
{
    unsigned int first;
    unsigned int second;
    unsigned int third;

    Rva1A94C0TripleZeroThunk *reset(int unused);
};

Rva1A94C0TripleZeroThunk *Rva1A94C0TripleZeroThunk::reset(int)
{
    first = 0;
    second = 0;
    third = 0;
    return this;
}
