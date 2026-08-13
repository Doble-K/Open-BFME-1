struct NonadenaryIdentityWithArgumentThunk
{
    NonadenaryIdentityWithArgumentThunk *identity(int unused);
};

NonadenaryIdentityWithArgumentThunk *NonadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
