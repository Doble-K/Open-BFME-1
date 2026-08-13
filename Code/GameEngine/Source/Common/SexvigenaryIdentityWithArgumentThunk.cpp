struct SexvigenaryIdentityWithArgumentThunk
{
    SexvigenaryIdentityWithArgumentThunk *identity(int unused);
};

SexvigenaryIdentityWithArgumentThunk *SexvigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
