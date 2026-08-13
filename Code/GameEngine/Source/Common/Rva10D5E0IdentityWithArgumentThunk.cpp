struct Rva10D5E0IdentityWithArgumentThunk
{
    Rva10D5E0IdentityWithArgumentThunk *identity(int unused);
};

Rva10D5E0IdentityWithArgumentThunk *Rva10D5E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
