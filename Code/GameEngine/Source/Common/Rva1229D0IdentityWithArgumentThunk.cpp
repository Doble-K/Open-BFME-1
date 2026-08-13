struct Rva1229D0IdentityWithArgumentThunk
{
    Rva1229D0IdentityWithArgumentThunk *identity(int unused);
};

Rva1229D0IdentityWithArgumentThunk *Rva1229D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
