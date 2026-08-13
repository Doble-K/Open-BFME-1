struct Rva1A4570IdentityWithArgumentThunk
{
    Rva1A4570IdentityWithArgumentThunk *identity(int unused);
};

Rva1A4570IdentityWithArgumentThunk *Rva1A4570IdentityWithArgumentThunk::identity(int)
{
    return this;
}
