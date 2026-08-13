struct RvaA7370IdentityWithArgumentThunk
{
    RvaA7370IdentityWithArgumentThunk *identity(int unused);
};

RvaA7370IdentityWithArgumentThunk *RvaA7370IdentityWithArgumentThunk::identity(int)
{
    return this;
}
