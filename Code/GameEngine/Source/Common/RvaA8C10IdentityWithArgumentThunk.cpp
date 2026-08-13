struct RvaA8C10IdentityWithArgumentThunk
{
    RvaA8C10IdentityWithArgumentThunk *identity(int unused);
};

RvaA8C10IdentityWithArgumentThunk *RvaA8C10IdentityWithArgumentThunk::identity(int)
{
    return this;
}
