struct MemberPointerOffset16Thunk
{
    char *value;

    void *get() const;
    void *getAlternate() const;
    void *getThird() const;
};

void *MemberPointerOffset16Thunk::get() const
{
    return value + 16;
}

void *MemberPointerOffset16Thunk::getAlternate() const
{
    return value + 16;
}

void *MemberPointerOffset16Thunk::getThird() const
{
    return value + 16;
}
