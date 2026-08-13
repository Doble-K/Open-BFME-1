struct Rva10D620IdentityWithArgumentThunk
{
    Rva10D620IdentityWithArgumentThunk *identity(int unused);
};

Rva10D620IdentityWithArgumentThunk *Rva10D620IdentityWithArgumentThunk::identity(int)
{
    return this;
}
