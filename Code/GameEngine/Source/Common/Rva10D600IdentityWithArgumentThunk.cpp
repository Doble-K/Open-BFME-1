struct Rva10D600IdentityWithArgumentThunk
{
    Rva10D600IdentityWithArgumentThunk *identity(int unused);
};

Rva10D600IdentityWithArgumentThunk *Rva10D600IdentityWithArgumentThunk::identity(int)
{
    return this;
}
