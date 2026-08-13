struct RvaF9410IdentityWithArgumentThunk
{
    RvaF9410IdentityWithArgumentThunk *identity(int unused);
};

RvaF9410IdentityWithArgumentThunk *RvaF9410IdentityWithArgumentThunk::identity(int)
{
    return this;
}
