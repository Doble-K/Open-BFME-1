struct ScalarValueResult
{
    unsigned long value;
};

struct ScalarValueReturnThunk
{
    unsigned long value;

    ScalarValueResult get() const;
    ScalarValueResult getAlternate() const;
    ScalarValueResult getThird() const;
    ScalarValueResult getFourth() const;
    ScalarValueResult getFifth() const;
    ScalarValueResult getSixth() const;
};

ScalarValueResult ScalarValueReturnThunk::get() const
{
    ScalarValueResult result = { value };
    return result;
}

ScalarValueResult ScalarValueReturnThunk::getAlternate() const
{
    ScalarValueResult result = { value };
    return result;
}

ScalarValueResult ScalarValueReturnThunk::getThird() const
{
    ScalarValueResult result = { value };
    return result;
}

ScalarValueResult ScalarValueReturnThunk::getFourth() const
{
    ScalarValueResult result = { value };
    return result;
}

ScalarValueResult ScalarValueReturnThunk::getFifth() const
{
    ScalarValueResult result = { value };
    return result;
}

ScalarValueResult ScalarValueReturnThunk::getSixth() const
{
    ScalarValueResult result = { value };
    return result;
}
