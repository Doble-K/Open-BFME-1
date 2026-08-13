struct Rva13D6B0IdentityWithArgumentThunk
{
    Rva13D6B0IdentityWithArgumentThunk *identity(int unused);
};

Rva13D6B0IdentityWithArgumentThunk *Rva13D6B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
