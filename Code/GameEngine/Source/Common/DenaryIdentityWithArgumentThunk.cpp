struct DenaryIdentityWithArgumentThunk
{
    DenaryIdentityWithArgumentThunk *identity(int unused);
};

DenaryIdentityWithArgumentThunk *DenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
