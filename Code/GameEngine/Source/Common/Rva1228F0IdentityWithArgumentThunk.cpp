struct Rva1228F0IdentityWithArgumentThunk
{
    Rva1228F0IdentityWithArgumentThunk *identity(int unused);
};

Rva1228F0IdentityWithArgumentThunk *Rva1228F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
