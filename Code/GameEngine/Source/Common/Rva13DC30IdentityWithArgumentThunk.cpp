struct Rva13DC30IdentityWithArgumentThunk
{
    Rva13DC30IdentityWithArgumentThunk *identity(int unused);
};

Rva13DC30IdentityWithArgumentThunk *Rva13DC30IdentityWithArgumentThunk::identity(int)
{
    return this;
}
