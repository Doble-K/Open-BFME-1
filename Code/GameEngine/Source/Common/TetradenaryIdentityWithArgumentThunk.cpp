struct TetradenaryIdentityWithArgumentThunk
{
    TetradenaryIdentityWithArgumentThunk *identity(int unused);
};

TetradenaryIdentityWithArgumentThunk *TetradenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
