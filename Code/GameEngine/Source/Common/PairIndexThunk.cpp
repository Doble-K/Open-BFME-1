struct PairIndexValue
{
    unsigned long first;
    unsigned long second;
};

struct PairIndexThunk
{
    PairIndexValue *values;

    PairIndexValue *at(unsigned long index) const;
};

PairIndexValue *PairIndexThunk::at(unsigned long index) const
{
    return values + index;
}
