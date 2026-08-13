struct RvaA0280IdentityWithArgumentThunk
{
    RvaA0280IdentityWithArgumentThunk *identity(int unused);
};

RvaA0280IdentityWithArgumentThunk *RvaA0280IdentityWithArgumentThunk::identity(int)
{
    return this;
}
