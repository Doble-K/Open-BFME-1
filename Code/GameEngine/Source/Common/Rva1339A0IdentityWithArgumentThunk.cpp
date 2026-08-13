struct Rva1339A0IdentityWithArgumentThunk
{
    Rva1339A0IdentityWithArgumentThunk *identity(int unused);
};

Rva1339A0IdentityWithArgumentThunk *Rva1339A0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
