struct FirstWordZeroInitializerThunk
{
    unsigned long value;

    FirstWordZeroInitializerThunk *initialize();
    FirstWordZeroInitializerThunk *initializeAlternate();
};

FirstWordZeroInitializerThunk *FirstWordZeroInitializerThunk::initialize()
{
    value = 0;
    return this;
}

FirstWordZeroInitializerThunk *FirstWordZeroInitializerThunk::initializeAlternate()
{
    value = 0;
    return this;
}
