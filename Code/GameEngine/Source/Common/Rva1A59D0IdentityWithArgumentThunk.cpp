struct Rva1A59D0IdentityWithArgumentThunk
{
    Rva1A59D0IdentityWithArgumentThunk *identity(int unused);
};

Rva1A59D0IdentityWithArgumentThunk *Rva1A59D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
