struct RvaEB1B0IdentityWithArgumentThunk
{
    RvaEB1B0IdentityWithArgumentThunk *identity(int unused);
};

RvaEB1B0IdentityWithArgumentThunk *RvaEB1B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
