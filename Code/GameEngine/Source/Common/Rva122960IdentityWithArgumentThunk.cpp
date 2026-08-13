struct Rva122960IdentityWithArgumentThunk
{
    Rva122960IdentityWithArgumentThunk *identity(int unused);
};

Rva122960IdentityWithArgumentThunk *Rva122960IdentityWithArgumentThunk::identity(int)
{
    return this;
}
