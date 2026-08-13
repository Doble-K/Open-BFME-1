struct Rva13D7D0IdentityWithArgumentThunk
{
    Rva13D7D0IdentityWithArgumentThunk *identity(int unused);
};

Rva13D7D0IdentityWithArgumentThunk *Rva13D7D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
