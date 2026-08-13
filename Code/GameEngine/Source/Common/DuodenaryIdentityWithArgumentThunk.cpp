struct DuodenaryIdentityWithArgumentThunk
{
    DuodenaryIdentityWithArgumentThunk *identity(int unused);
};

DuodenaryIdentityWithArgumentThunk *DuodenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
