struct Rva13D7C0IdentityWithArgumentThunk
{
    Rva13D7C0IdentityWithArgumentThunk *identity(int unused);
};

Rva13D7C0IdentityWithArgumentThunk *Rva13D7C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
