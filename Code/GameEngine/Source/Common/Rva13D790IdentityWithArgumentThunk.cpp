struct Rva13D790IdentityWithArgumentThunk
{
    Rva13D790IdentityWithArgumentThunk *identity(int unused);
};

Rva13D790IdentityWithArgumentThunk *Rva13D790IdentityWithArgumentThunk::identity(int)
{
    return this;
}
