struct RvaA8BA0IdentityWithArgumentThunk
{
    RvaA8BA0IdentityWithArgumentThunk *identity(int unused);
};

RvaA8BA0IdentityWithArgumentThunk *RvaA8BA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
