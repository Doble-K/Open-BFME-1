struct NovemvigenaryIdentityWithArgumentThunk
{
    NovemvigenaryIdentityWithArgumentThunk *identity(int unused);
};

NovemvigenaryIdentityWithArgumentThunk *NovemvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
