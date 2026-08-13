struct RvaCAFF0IdentityWithArgumentThunk
{
    RvaCAFF0IdentityWithArgumentThunk *identity(int unused);
};

RvaCAFF0IdentityWithArgumentThunk *RvaCAFF0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
