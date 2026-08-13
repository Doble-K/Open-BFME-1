struct Rva13D5E0IdentityWithArgumentThunk
{
    Rva13D5E0IdentityWithArgumentThunk *identity(int unused);
};

Rva13D5E0IdentityWithArgumentThunk *Rva13D5E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
