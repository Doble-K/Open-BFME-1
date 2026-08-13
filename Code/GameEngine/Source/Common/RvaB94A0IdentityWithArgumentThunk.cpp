struct RvaB94A0IdentityWithArgumentThunk
{
    RvaB94A0IdentityWithArgumentThunk *identity(int unused);
};

RvaB94A0IdentityWithArgumentThunk *RvaB94A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
