struct RvaED070IdentityWithArgumentThunk
{
    RvaED070IdentityWithArgumentThunk *identity(int unused);
};

RvaED070IdentityWithArgumentThunk *RvaED070IdentityWithArgumentThunk::identity(int)
{
    return this;
}
