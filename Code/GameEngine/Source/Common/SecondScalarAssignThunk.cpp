struct SecondScalarAssignThunk
{
    unsigned long value;

    SecondScalarAssignThunk &assign(unsigned long ignored, unsigned long newValue);
    SecondScalarAssignThunk &assignAlternate(unsigned long ignored, unsigned long newValue);
};

SecondScalarAssignThunk &SecondScalarAssignThunk::assign(unsigned long, unsigned long newValue)
{
    value = newValue;
    return *this;
}

SecondScalarAssignThunk &SecondScalarAssignThunk::assignAlternate(unsigned long, unsigned long newValue)
{
    value = newValue;
    return *this;
}
