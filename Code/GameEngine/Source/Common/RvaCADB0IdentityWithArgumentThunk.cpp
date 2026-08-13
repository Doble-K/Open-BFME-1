struct RvaCADB0IdentityWithArgumentThunk
{
    RvaCADB0IdentityWithArgumentThunk *identity(int unused);
};

RvaCADB0IdentityWithArgumentThunk *RvaCADB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
