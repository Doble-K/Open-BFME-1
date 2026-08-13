struct RvaE4440IdentityWithArgumentThunk
{
    RvaE4440IdentityWithArgumentThunk *identity(int unused);
};

RvaE4440IdentityWithArgumentThunk *RvaE4440IdentityWithArgumentThunk::identity(int)
{
    return this;
}
