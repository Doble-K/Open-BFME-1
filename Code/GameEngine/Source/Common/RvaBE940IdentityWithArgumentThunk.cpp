struct RvaBE940IdentityWithArgumentThunk
{
    RvaBE940IdentityWithArgumentThunk *identity(int unused);
};

RvaBE940IdentityWithArgumentThunk *RvaBE940IdentityWithArgumentThunk::identity(int)
{
    return this;
}
