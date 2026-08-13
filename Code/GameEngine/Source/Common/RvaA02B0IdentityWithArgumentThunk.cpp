struct RvaA02B0IdentityWithArgumentThunk
{
    RvaA02B0IdentityWithArgumentThunk *identity(int unused);
};

RvaA02B0IdentityWithArgumentThunk *RvaA02B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
