struct Rva13A3F0IdentityWithArgumentThunk
{
    Rva13A3F0IdentityWithArgumentThunk *identity(int unused);
};

Rva13A3F0IdentityWithArgumentThunk *Rva13A3F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
