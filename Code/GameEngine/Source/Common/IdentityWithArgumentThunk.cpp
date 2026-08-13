struct IdentityWithArgumentThunk
{
    IdentityWithArgumentThunk *identity(int unused);
};

IdentityWithArgumentThunk *IdentityWithArgumentThunk::identity(int)
{
    return this;
}
