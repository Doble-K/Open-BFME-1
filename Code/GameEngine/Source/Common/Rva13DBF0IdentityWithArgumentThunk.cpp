struct Rva13DBF0IdentityWithArgumentThunk
{
    Rva13DBF0IdentityWithArgumentThunk *identity(int unused);
};

Rva13DBF0IdentityWithArgumentThunk *Rva13DBF0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
