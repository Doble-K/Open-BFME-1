struct Rva879F0IdentityWithArgumentThunk
{
    Rva879F0IdentityWithArgumentThunk *identity(int unused);
};

Rva879F0IdentityWithArgumentThunk *Rva879F0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
