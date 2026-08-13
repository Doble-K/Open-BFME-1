struct Rva13A410IdentityWithArgumentThunk
{
    Rva13A410IdentityWithArgumentThunk *identity(int unused);
};

Rva13A410IdentityWithArgumentThunk *Rva13A410IdentityWithArgumentThunk::identity(int)
{
    return this;
}
