struct RvaBE8E0IdentityWithArgumentThunk
{
    RvaBE8E0IdentityWithArgumentThunk *identity(int unused);
};

RvaBE8E0IdentityWithArgumentThunk *RvaBE8E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
