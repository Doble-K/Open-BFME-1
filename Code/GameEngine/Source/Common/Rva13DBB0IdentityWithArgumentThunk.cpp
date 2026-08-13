struct Rva13DBB0IdentityWithArgumentThunk
{
    Rva13DBB0IdentityWithArgumentThunk *identity(int unused);
};

Rva13DBB0IdentityWithArgumentThunk *Rva13DBB0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
