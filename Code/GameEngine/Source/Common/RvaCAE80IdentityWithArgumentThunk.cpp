struct RvaCAE80IdentityWithArgumentThunk
{
    RvaCAE80IdentityWithArgumentThunk *identity(int unused);
};

RvaCAE80IdentityWithArgumentThunk *RvaCAE80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
