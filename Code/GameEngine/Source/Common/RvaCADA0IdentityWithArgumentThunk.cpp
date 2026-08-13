struct RvaCADA0IdentityWithArgumentThunk
{
    RvaCADA0IdentityWithArgumentThunk *identity(int unused);
};

RvaCADA0IdentityWithArgumentThunk *RvaCADA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
