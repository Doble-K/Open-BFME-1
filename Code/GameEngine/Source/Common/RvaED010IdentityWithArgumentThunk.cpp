struct RvaED010IdentityWithArgumentThunk
{
    RvaED010IdentityWithArgumentThunk *identity(int unused);
};

RvaED010IdentityWithArgumentThunk *RvaED010IdentityWithArgumentThunk::identity(int)
{
    return this;
}
