struct Rva122AA0IdentityWithArgumentThunk
{
    Rva122AA0IdentityWithArgumentThunk *identity(int unused);
};

Rva122AA0IdentityWithArgumentThunk *Rva122AA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
