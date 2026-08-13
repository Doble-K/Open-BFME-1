struct NestedFieldValues
{
    unsigned long prefix[6];
    unsigned long first;
    unsigned long second;
    unsigned long third;
};

struct NestedFieldGetterThunk
{
    unsigned long unused;
    NestedFieldValues *values;

    unsigned long getFirst() const;
};

unsigned long NestedFieldGetterThunk::getFirst() const
{
    return values->first;
}
