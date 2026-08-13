struct RvaA8B70IdentityWithArgumentThunk
{
    RvaA8B70IdentityWithArgumentThunk *identity(int unused);
};

RvaA8B70IdentityWithArgumentThunk *RvaA8B70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
