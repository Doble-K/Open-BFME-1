struct Rva13D990IdentityWithArgumentThunk
{
    Rva13D990IdentityWithArgumentThunk *identity(int unused);
};

Rva13D990IdentityWithArgumentThunk *Rva13D990IdentityWithArgumentThunk::identity(int)
{
    return this;
}
