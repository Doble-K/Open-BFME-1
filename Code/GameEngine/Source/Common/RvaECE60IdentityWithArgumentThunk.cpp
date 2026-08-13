struct RvaECE60IdentityWithArgumentThunk
{
    RvaECE60IdentityWithArgumentThunk *identity(int unused);
};

RvaECE60IdentityWithArgumentThunk *RvaECE60IdentityWithArgumentThunk::identity(int)
{
    return this;
}
