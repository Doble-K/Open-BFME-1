struct RvaECE70IdentityWithArgumentThunk
{
    RvaECE70IdentityWithArgumentThunk *identity(int unused);
};

RvaECE70IdentityWithArgumentThunk *RvaECE70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
