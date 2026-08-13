struct TridenaryIdentityWithArgumentThunk
{
    TridenaryIdentityWithArgumentThunk *identity(int unused);
};

TridenaryIdentityWithArgumentThunk *TridenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
