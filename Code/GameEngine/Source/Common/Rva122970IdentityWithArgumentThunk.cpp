struct Rva122970IdentityWithArgumentThunk
{
    Rva122970IdentityWithArgumentThunk *identity(int unused);
};

Rva122970IdentityWithArgumentThunk *Rva122970IdentityWithArgumentThunk::identity(int)
{
    return this;
}
