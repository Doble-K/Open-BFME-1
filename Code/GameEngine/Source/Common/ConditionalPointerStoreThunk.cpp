struct ConditionalPointerStoreThunk
{
    unsigned long first;
    void *second;
    void *stored;

    void *storeIfNotNull(void *value);
    void *storeSecondIfNotNull(void *value);
    void *takeStored();
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

void *ConditionalPointerStoreThunk::takeStored()
{
    void *result = stored;
    stored = 0;
    return result;
}

void *ConditionalPointerStoreThunk::storeSecondIfNotNull(void *value)
{
    if (value)
    {
        second = value;
        return value;
    }

    return 0;
}
