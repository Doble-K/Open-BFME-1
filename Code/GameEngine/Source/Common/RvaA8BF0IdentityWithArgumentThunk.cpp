struct RvaA8BF0IdentityWithArgumentThunk
{
    RvaA8BF0IdentityWithArgumentThunk *identity(int unused);
};

RvaA8BF0IdentityWithArgumentThunk *RvaA8BF0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
