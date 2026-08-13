struct RvaAFBC0IdentityWithArgumentThunk
{
    RvaAFBC0IdentityWithArgumentThunk *identity(int unused);
};

RvaAFBC0IdentityWithArgumentThunk *RvaAFBC0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
