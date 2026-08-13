struct Rva13D7B0IdentityWithArgumentThunk
{
    Rva13D7B0IdentityWithArgumentThunk *identity(int unused);
};

Rva13D7B0IdentityWithArgumentThunk *Rva13D7B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
