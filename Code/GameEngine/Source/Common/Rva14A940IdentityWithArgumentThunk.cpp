struct Rva14A940IdentityWithArgumentThunk
{
    Rva14A940IdentityWithArgumentThunk *identity(int unused);
};

Rva14A940IdentityWithArgumentThunk *Rva14A940IdentityWithArgumentThunk::identity(int)
{
    return this;
}
