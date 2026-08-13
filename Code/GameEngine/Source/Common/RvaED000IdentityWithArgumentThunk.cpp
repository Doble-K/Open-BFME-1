struct RvaED000IdentityWithArgumentThunk
{
    RvaED000IdentityWithArgumentThunk *identity(int unused);
};

RvaED000IdentityWithArgumentThunk *RvaED000IdentityWithArgumentThunk::identity(int)
{
    return this;
}
