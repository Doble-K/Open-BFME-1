struct Rva10D630IdentityWithArgumentThunk
{
    Rva10D630IdentityWithArgumentThunk *identity(int unused);
};

Rva10D630IdentityWithArgumentThunk *Rva10D630IdentityWithArgumentThunk::identity(int)
{
    return this;
}
