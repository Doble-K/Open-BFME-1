struct RvaFC4D0IdentityWithArgumentThunk
{
    RvaFC4D0IdentityWithArgumentThunk *identity(int unused);
};

RvaFC4D0IdentityWithArgumentThunk *RvaFC4D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
