struct ScalarIndexThunk
{
    unsigned long *values;

    unsigned long *at(unsigned long index) const;
};

unsigned long *ScalarIndexThunk::at(unsigned long index) const
{
    return values + index;
}
