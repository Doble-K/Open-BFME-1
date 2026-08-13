struct UndenaryIdentityWithArgumentThunk
{
    UndenaryIdentityWithArgumentThunk *identity(int unused);
};

UndenaryIdentityWithArgumentThunk *UndenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
