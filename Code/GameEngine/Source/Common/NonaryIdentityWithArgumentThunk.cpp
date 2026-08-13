struct NonaryIdentityWithArgumentThunk
{
    NonaryIdentityWithArgumentThunk *identity(int unused);
};

NonaryIdentityWithArgumentThunk *NonaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
