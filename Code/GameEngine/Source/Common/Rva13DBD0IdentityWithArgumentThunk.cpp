struct Rva13DBD0IdentityWithArgumentThunk
{
    Rva13DBD0IdentityWithArgumentThunk *identity(int unused);
};

Rva13DBD0IdentityWithArgumentThunk *Rva13DBD0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
