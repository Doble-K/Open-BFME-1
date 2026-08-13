struct RvaED090IdentityWithArgumentThunk
{
    RvaED090IdentityWithArgumentThunk *identity(int unused);
};

RvaED090IdentityWithArgumentThunk *RvaED090IdentityWithArgumentThunk::identity(int)
{
    return this;
}
