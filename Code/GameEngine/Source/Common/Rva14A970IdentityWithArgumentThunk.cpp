struct Rva14A970IdentityWithArgumentThunk
{
    Rva14A970IdentityWithArgumentThunk *identity(int unused);
};

Rva14A970IdentityWithArgumentThunk *Rva14A970IdentityWithArgumentThunk::identity(int)
{
    return this;
}
