struct RvaAF7F0IdentityWithArgumentThunk
{
    RvaAF7F0IdentityWithArgumentThunk *identity(int unused);
};

RvaAF7F0IdentityWithArgumentThunk *RvaAF7F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
