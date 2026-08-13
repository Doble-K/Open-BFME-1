struct RvaA8C00IdentityWithArgumentThunk
{
    RvaA8C00IdentityWithArgumentThunk *identity(int unused);
};

RvaA8C00IdentityWithArgumentThunk *RvaA8C00IdentityWithArgumentThunk::identity(int)
{
    return this;
}
