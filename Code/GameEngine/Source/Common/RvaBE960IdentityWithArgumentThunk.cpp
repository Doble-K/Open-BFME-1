struct RvaBE960IdentityWithArgumentThunk
{
    RvaBE960IdentityWithArgumentThunk *identity(int unused);
};

RvaBE960IdentityWithArgumentThunk *RvaBE960IdentityWithArgumentThunk::identity(int)
{
    return this;
}
