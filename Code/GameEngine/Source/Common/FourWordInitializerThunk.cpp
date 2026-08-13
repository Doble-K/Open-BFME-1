struct FourWordInitializerThunk
{
    unsigned long tag;
    unsigned long first;
    unsigned long second;
    unsigned long third;

    FourWordInitializerThunk *initialize(unsigned long firstValue, unsigned long secondValue, unsigned long thirdValue);
};

FourWordInitializerThunk *FourWordInitializerThunk::initialize(
    unsigned long firstValue, unsigned long secondValue, unsigned long thirdValue)
{
    tag = 1;
    first = firstValue;
    second = secondValue;
    third = thirdValue;
    return this;
}
