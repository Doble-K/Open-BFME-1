struct Rva13DBE0IdentityWithArgumentThunk
{
    Rva13DBE0IdentityWithArgumentThunk *identity(int unused);
};

Rva13DBE0IdentityWithArgumentThunk *Rva13DBE0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
