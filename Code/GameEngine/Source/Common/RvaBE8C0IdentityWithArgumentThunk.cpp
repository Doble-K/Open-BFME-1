struct RvaBE8C0IdentityWithArgumentThunk
{
    RvaBE8C0IdentityWithArgumentThunk *identity(int unused);
};

RvaBE8C0IdentityWithArgumentThunk *RvaBE8C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
