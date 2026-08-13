struct Rva1A4600IdentityWithArgumentThunk
{
    Rva1A4600IdentityWithArgumentThunk *identity(int unused);
};

Rva1A4600IdentityWithArgumentThunk *Rva1A4600IdentityWithArgumentThunk::identity(int)
{
    return this;
}
