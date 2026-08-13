struct Rva9EC80IdentityWithArgumentThunk
{
    Rva9EC80IdentityWithArgumentThunk *identity(int unused);
};

Rva9EC80IdentityWithArgumentThunk *Rva9EC80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
