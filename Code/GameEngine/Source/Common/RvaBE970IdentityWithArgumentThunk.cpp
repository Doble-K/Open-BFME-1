struct RvaBE970IdentityWithArgumentThunk
{
    RvaBE970IdentityWithArgumentThunk *identity(int unused);
};

RvaBE970IdentityWithArgumentThunk *RvaBE970IdentityWithArgumentThunk::identity(int)
{
    return this;
}
