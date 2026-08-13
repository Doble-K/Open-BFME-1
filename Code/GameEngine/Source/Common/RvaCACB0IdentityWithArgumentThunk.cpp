struct RvaCACB0IdentityWithArgumentThunk
{
    RvaCACB0IdentityWithArgumentThunk *identity(int unused);
};

RvaCACB0IdentityWithArgumentThunk *RvaCACB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
