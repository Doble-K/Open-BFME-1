struct Rva1229C0IdentityWithArgumentThunk
{
    Rva1229C0IdentityWithArgumentThunk *identity(int unused);
};

Rva1229C0IdentityWithArgumentThunk *Rva1229C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
