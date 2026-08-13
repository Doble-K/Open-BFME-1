struct RvaCACA0IdentityWithArgumentThunk
{
    RvaCACA0IdentityWithArgumentThunk *identity(int unused);
};

RvaCACA0IdentityWithArgumentThunk *RvaCACA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
