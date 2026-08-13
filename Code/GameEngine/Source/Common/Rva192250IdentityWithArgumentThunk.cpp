struct Rva192250IdentityWithArgumentThunk
{
    Rva192250IdentityWithArgumentThunk *identity(int unused);
};

Rva192250IdentityWithArgumentThunk *Rva192250IdentityWithArgumentThunk::identity(int)
{
    return this;
}
