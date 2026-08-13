struct ScalarCopyAssignThunk
{
    unsigned long value;

    ScalarCopyAssignThunk &assign(const ScalarCopyAssignThunk &other);
};

ScalarCopyAssignThunk &ScalarCopyAssignThunk::assign(const ScalarCopyAssignThunk &other)
{
    value = other.value;
    return *this;
}
