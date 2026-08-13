struct Rva10D5D0IdentityWithArgumentThunk
{
    Rva10D5D0IdentityWithArgumentThunk *identity(int unused);
};

Rva10D5D0IdentityWithArgumentThunk *Rva10D5D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
