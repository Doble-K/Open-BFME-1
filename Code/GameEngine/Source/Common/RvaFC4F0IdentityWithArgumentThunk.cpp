struct RvaFC4F0IdentityWithArgumentThunk
{
    RvaFC4F0IdentityWithArgumentThunk *identity(int unused);
};

RvaFC4F0IdentityWithArgumentThunk *RvaFC4F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
