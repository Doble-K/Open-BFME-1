struct SecondaryIdentityWithArgumentThunk
{
    SecondaryIdentityWithArgumentThunk *identity(int unused);
};

SecondaryIdentityWithArgumentThunk *SecondaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
