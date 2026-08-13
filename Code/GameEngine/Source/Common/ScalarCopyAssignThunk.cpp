struct ScalarCopyAssignThunk
{
    unsigned long value;

    ScalarCopyAssignThunk &assign(const ScalarCopyAssignThunk &other);
    ScalarCopyAssignThunk &assignAlternate(const ScalarCopyAssignThunk &other);
};

ScalarCopyAssignThunk &ScalarCopyAssignThunk::assign(const ScalarCopyAssignThunk &other)
{
    value = other.value;
    return *this;
}

ScalarCopyAssignThunk &ScalarCopyAssignThunk::assignAlternate(const ScalarCopyAssignThunk &other)
{
    value = other.value;
    return *this;
}
