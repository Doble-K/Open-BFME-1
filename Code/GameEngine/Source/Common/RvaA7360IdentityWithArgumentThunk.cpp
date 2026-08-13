struct RvaA7360IdentityWithArgumentThunk
{
    RvaA7360IdentityWithArgumentThunk *identity(int unused);
};

RvaA7360IdentityWithArgumentThunk *RvaA7360IdentityWithArgumentThunk::identity(int)
{
    return this;
}
