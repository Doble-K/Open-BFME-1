struct ConditionalPointerStoreThunk
{
    unsigned long first;
    unsigned long second;
    void *stored;

    void *storeIfNotNull(void *value);
};

void *ConditionalPointerStoreThunk::storeIfNotNull(void *value)
{
    if (value)
    {
        stored = value;
        return value;
    }

    return 0;
}
