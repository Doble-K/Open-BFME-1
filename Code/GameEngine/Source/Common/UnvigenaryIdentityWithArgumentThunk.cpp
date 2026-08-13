struct UnvigenaryIdentityWithArgumentThunk
{
    UnvigenaryIdentityWithArgumentThunk *identity(int unused);
};

UnvigenaryIdentityWithArgumentThunk *UnvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
