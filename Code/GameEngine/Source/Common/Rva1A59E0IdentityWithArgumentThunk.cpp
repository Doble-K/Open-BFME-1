struct Rva1A59E0IdentityWithArgumentThunk
{
    Rva1A59E0IdentityWithArgumentThunk *identity(int unused);
};

Rva1A59E0IdentityWithArgumentThunk *Rva1A59E0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
