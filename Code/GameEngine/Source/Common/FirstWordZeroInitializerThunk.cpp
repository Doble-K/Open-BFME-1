struct FirstWordZeroInitializerThunk
{
    unsigned long value;

    FirstWordZeroInitializerThunk *initialize();
};

FirstWordZeroInitializerThunk *FirstWordZeroInitializerThunk::initialize()
{
    value = 0;
    return this;
}
