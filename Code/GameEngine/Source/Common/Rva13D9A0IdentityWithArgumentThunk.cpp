struct Rva13D9A0IdentityWithArgumentThunk
{
    Rva13D9A0IdentityWithArgumentThunk *identity(int unused);
};

Rva13D9A0IdentityWithArgumentThunk *Rva13D9A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
