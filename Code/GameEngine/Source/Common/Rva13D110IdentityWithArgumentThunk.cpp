struct Rva13D110IdentityWithArgumentThunk
{
    Rva13D110IdentityWithArgumentThunk *identity(int unused);
};

Rva13D110IdentityWithArgumentThunk *Rva13D110IdentityWithArgumentThunk::identity(int)
{
    return this;
}
