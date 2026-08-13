struct Rva191F40IdentityWithArgumentThunk
{
    Rva191F40IdentityWithArgumentThunk *identity(int unused);
};

Rva191F40IdentityWithArgumentThunk *Rva191F40IdentityWithArgumentThunk::identity(int)
{
    return this;
}
