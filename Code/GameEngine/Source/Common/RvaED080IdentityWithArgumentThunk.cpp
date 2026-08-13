struct RvaED080IdentityWithArgumentThunk
{
    RvaED080IdentityWithArgumentThunk *identity(int unused);
};

RvaED080IdentityWithArgumentThunk *RvaED080IdentityWithArgumentThunk::identity(int)
{
    return this;
}
