struct OctadenaryIdentityWithArgumentThunk
{
    OctadenaryIdentityWithArgumentThunk *identity(int unused);
};

OctadenaryIdentityWithArgumentThunk *OctadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
