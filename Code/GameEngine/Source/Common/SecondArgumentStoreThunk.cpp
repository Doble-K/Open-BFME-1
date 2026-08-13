struct SecondArgumentStoreThunk
{
    unsigned long value;

    SecondArgumentStoreThunk *setFromSecondArgument(unsigned long unused, unsigned long newValue);
};

SecondArgumentStoreThunk *SecondArgumentStoreThunk::setFromSecondArgument(unsigned long, unsigned long newValue)
{
    value = newValue;
    return this;
}
