struct OctovigenaryIdentityWithArgumentThunk
{
    OctovigenaryIdentityWithArgumentThunk *identity(int unused);
};

OctovigenaryIdentityWithArgumentThunk *OctovigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
