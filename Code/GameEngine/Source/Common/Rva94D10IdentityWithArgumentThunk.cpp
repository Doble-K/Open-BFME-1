struct Rva94D10IdentityWithArgumentThunk
{
    Rva94D10IdentityWithArgumentThunk *identity(int unused);
};

Rva94D10IdentityWithArgumentThunk *Rva94D10IdentityWithArgumentThunk::identity(int)
{
    return this;
}
