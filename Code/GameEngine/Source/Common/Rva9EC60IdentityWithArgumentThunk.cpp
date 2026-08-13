struct Rva9EC60IdentityWithArgumentThunk
{
    Rva9EC60IdentityWithArgumentThunk *identity(int unused);
};

Rva9EC60IdentityWithArgumentThunk *Rva9EC60IdentityWithArgumentThunk::identity(int)
{
    return this;
}
