struct MemberPointerOffset16Thunk
{
    char *value;

    void *get() const;
};

void *MemberPointerOffset16Thunk::get() const
{
    return value + 16;
}
