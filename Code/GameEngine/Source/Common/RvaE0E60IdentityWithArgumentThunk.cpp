struct RvaE0E60IdentityWithArgumentThunk
{
    RvaE0E60IdentityWithArgumentThunk *identity(int unused);
};

RvaE0E60IdentityWithArgumentThunk *RvaE0E60IdentityWithArgumentThunk::identity(int)
{
    return this;
}
