struct ScalarValueResult
{
    unsigned long value;
};

struct ScalarValueReturnThunk
{
    unsigned long value;

    ScalarValueResult get() const;
};

ScalarValueResult ScalarValueReturnThunk::get() const
{
    ScalarValueResult result = { value };
    return result;
}
