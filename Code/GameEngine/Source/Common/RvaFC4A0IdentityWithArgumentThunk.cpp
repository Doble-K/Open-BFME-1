struct RvaFC4A0IdentityWithArgumentThunk
{
    RvaFC4A0IdentityWithArgumentThunk *identity(int unused);
};

RvaFC4A0IdentityWithArgumentThunk *RvaFC4A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
