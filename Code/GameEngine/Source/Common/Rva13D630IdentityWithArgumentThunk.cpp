struct Rva13D630IdentityWithArgumentThunk
{
    Rva13D630IdentityWithArgumentThunk *identity(int unused);
};

Rva13D630IdentityWithArgumentThunk *Rva13D630IdentityWithArgumentThunk::identity(int)
{
    return this;
}
