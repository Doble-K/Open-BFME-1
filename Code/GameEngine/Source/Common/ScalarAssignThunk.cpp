struct ScalarAssignThunk
{
    unsigned long value;

    ScalarAssignThunk &assign(unsigned long newValue);
};

ScalarAssignThunk &ScalarAssignThunk::assign(unsigned long newValue)
{
    value = newValue;
    return *this;
}
