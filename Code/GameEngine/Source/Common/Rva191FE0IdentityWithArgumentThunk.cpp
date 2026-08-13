struct Rva191FE0IdentityWithArgumentThunk
{
    Rva191FE0IdentityWithArgumentThunk *identity(int unused);
};

Rva191FE0IdentityWithArgumentThunk *Rva191FE0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
