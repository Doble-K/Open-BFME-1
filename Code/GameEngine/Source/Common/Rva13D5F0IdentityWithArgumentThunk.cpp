struct Rva13D5F0IdentityWithArgumentThunk
{
    Rva13D5F0IdentityWithArgumentThunk *identity(int unused);
};

Rva13D5F0IdentityWithArgumentThunk *Rva13D5F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
