struct QuinvigenaryIdentityWithArgumentThunk
{
    QuinvigenaryIdentityWithArgumentThunk *identity(int unused);
};

QuinvigenaryIdentityWithArgumentThunk *QuinvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
