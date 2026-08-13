struct RvaECFF0IdentityWithArgumentThunk
{
    RvaECFF0IdentityWithArgumentThunk *identity(int unused);
};

RvaECFF0IdentityWithArgumentThunk *RvaECFF0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
