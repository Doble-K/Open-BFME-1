struct Rva9EC70IdentityWithArgumentThunk
{
    Rva9EC70IdentityWithArgumentThunk *identity(int unused);
};

Rva9EC70IdentityWithArgumentThunk *Rva9EC70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
