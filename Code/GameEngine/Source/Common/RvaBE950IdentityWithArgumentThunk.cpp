struct RvaBE950IdentityWithArgumentThunk
{
    RvaBE950IdentityWithArgumentThunk *identity(int unused);
};

RvaBE950IdentityWithArgumentThunk *RvaBE950IdentityWithArgumentThunk::identity(int)
{
    return this;
}
