struct Rva14A930IdentityWithArgumentThunk
{
    Rva14A930IdentityWithArgumentThunk *identity(int unused);
};

Rva14A930IdentityWithArgumentThunk *Rva14A930IdentityWithArgumentThunk::identity(int)
{
    return this;
}
