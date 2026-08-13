struct RvaED020IdentityWithArgumentThunk
{
    RvaED020IdentityWithArgumentThunk *identity(int unused);
};

RvaED020IdentityWithArgumentThunk *RvaED020IdentityWithArgumentThunk::identity(int)
{
    return this;
}
