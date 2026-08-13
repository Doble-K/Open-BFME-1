struct RvaFC500IdentityWithArgumentThunk
{
    RvaFC500IdentityWithArgumentThunk *identity(int unused);
};

RvaFC500IdentityWithArgumentThunk *RvaFC500IdentityWithArgumentThunk::identity(int)
{
    return this;
}
