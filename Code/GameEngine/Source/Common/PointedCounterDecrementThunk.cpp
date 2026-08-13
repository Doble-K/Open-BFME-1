struct PointedCounterDecrementThunk
{
    int *counter;

    void decrement();
};

void PointedCounterDecrementThunk::decrement()
{
    --*counter;
}
