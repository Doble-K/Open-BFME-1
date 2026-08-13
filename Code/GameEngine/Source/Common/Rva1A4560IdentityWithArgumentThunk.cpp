struct Rva1A4560IdentityWithArgumentThunk
{
    Rva1A4560IdentityWithArgumentThunk *identity(int unused);
};

Rva1A4560IdentityWithArgumentThunk *Rva1A4560IdentityWithArgumentThunk::identity(int)
{
    return this;
}
