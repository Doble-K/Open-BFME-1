struct VigenaryIdentityWithArgumentThunk
{
    VigenaryIdentityWithArgumentThunk *identity(int unused);
};

VigenaryIdentityWithArgumentThunk *VigenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
