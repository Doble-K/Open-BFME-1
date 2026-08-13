struct Rva1331C0IdentityWithArgumentThunk
{
    Rva1331C0IdentityWithArgumentThunk *identity(int unused);
};

Rva1331C0IdentityWithArgumentThunk *Rva1331C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
