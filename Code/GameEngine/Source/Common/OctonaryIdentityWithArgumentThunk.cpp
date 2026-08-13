struct OctonaryIdentityWithArgumentThunk
{
    OctonaryIdentityWithArgumentThunk *identity(int unused);
};

OctonaryIdentityWithArgumentThunk *OctonaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
