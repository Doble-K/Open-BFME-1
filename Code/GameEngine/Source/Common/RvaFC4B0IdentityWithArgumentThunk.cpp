struct RvaFC4B0IdentityWithArgumentThunk
{
    RvaFC4B0IdentityWithArgumentThunk *identity(int unused);
};

RvaFC4B0IdentityWithArgumentThunk *RvaFC4B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
