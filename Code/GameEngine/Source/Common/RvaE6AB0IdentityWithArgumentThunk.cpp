struct RvaE6AB0IdentityWithArgumentThunk
{
    RvaE6AB0IdentityWithArgumentThunk *identity(int unused);
};

RvaE6AB0IdentityWithArgumentThunk *RvaE6AB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
