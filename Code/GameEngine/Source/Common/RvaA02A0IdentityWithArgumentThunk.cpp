struct RvaA02A0IdentityWithArgumentThunk
{
    RvaA02A0IdentityWithArgumentThunk *identity(int unused);
};

RvaA02A0IdentityWithArgumentThunk *RvaA02A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
