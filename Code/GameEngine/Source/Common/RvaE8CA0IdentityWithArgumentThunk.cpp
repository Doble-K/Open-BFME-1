struct RvaE8CA0IdentityWithArgumentThunk
{
    RvaE8CA0IdentityWithArgumentThunk *identity(int unused);
};

RvaE8CA0IdentityWithArgumentThunk *RvaE8CA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
