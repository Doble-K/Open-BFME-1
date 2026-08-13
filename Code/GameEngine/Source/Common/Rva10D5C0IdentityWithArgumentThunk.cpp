struct Rva10D5C0IdentityWithArgumentThunk
{
    Rva10D5C0IdentityWithArgumentThunk *identity(int unused);
};

Rva10D5C0IdentityWithArgumentThunk *Rva10D5C0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
