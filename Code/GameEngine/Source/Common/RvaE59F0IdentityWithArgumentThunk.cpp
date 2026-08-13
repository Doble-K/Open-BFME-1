struct RvaE59F0IdentityWithArgumentThunk
{
    RvaE59F0IdentityWithArgumentThunk *identity(int unused);
};

RvaE59F0IdentityWithArgumentThunk *RvaE59F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
