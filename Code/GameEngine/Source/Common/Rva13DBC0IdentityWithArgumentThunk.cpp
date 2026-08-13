struct Rva13DBC0IdentityWithArgumentThunk
{
    Rva13DBC0IdentityWithArgumentThunk *identity(int unused);
};

Rva13DBC0IdentityWithArgumentThunk *Rva13DBC0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
