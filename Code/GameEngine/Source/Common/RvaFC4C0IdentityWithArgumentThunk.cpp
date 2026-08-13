struct RvaFC4C0IdentityWithArgumentThunk
{
    RvaFC4C0IdentityWithArgumentThunk *identity(int unused);
};

RvaFC4C0IdentityWithArgumentThunk *RvaFC4C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
