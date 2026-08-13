struct RvaAFBB0IdentityWithArgumentThunk
{
    RvaAFBB0IdentityWithArgumentThunk *identity(int unused);
};

RvaAFBB0IdentityWithArgumentThunk *RvaAFBB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
