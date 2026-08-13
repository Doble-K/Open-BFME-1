struct ScalarAssignThunk
{
    unsigned long value;

    ScalarAssignThunk &assign(unsigned long newValue);
    ScalarAssignThunk &assignAlternate(unsigned long newValue);
};

ScalarAssignThunk &ScalarAssignThunk::assign(unsigned long newValue)
{
    value = newValue;
    return *this;
}

ScalarAssignThunk &ScalarAssignThunk::assignAlternate(unsigned long newValue)
{
    value = newValue;
    return *this;
}
