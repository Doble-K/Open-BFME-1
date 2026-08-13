struct ScalarByteAssignThunk
{
    unsigned long scalar;
    unsigned char flag;

    ScalarByteAssignThunk &assign(const unsigned long *newScalar, const unsigned char *newFlag);
    ScalarByteAssignThunk &assignAlternate(const unsigned long *newScalar, const unsigned char *newFlag);
};

ScalarByteAssignThunk &ScalarByteAssignThunk::assign(
    const unsigned long *newScalar,
    const unsigned char *newFlag)
{
    scalar = *newScalar;
    flag = *newFlag;
    return *this;
}

ScalarByteAssignThunk &ScalarByteAssignThunk::assignAlternate(
    const unsigned long *newScalar,
    const unsigned char *newFlag)
{
    scalar = *newScalar;
    flag = *newFlag;
    return *this;
}
