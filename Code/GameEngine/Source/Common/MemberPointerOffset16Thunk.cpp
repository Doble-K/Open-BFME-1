struct MemberPointerOffset16Thunk
{
    char *value;

    void *get() const;
    void *getAlternate() const;
};

void *MemberPointerOffset16Thunk::get() const
{
    return value + 16;
}

void *MemberPointerOffset16Thunk::getAlternate() const
{
    return value + 16;
}
