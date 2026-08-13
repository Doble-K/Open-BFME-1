struct Rva1A45D0IdentityWithArgumentThunk
{
    Rva1A45D0IdentityWithArgumentThunk *identity(int unused);
};

Rva1A45D0IdentityWithArgumentThunk *Rva1A45D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
