struct Rva191FC0IdentityWithArgumentThunk
{
    Rva191FC0IdentityWithArgumentThunk *identity(int unused);
};

Rva191FC0IdentityWithArgumentThunk *Rva191FC0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
