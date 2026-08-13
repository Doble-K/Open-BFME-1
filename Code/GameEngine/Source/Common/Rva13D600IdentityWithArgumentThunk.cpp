struct Rva13D600IdentityWithArgumentThunk
{
    Rva13D600IdentityWithArgumentThunk *identity(int unused);
};

Rva13D600IdentityWithArgumentThunk *Rva13D600IdentityWithArgumentThunk::identity(int)
{
    return this;
}
