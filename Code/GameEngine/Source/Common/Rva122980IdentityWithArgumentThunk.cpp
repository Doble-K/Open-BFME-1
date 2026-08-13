struct Rva122980IdentityWithArgumentThunk
{
    Rva122980IdentityWithArgumentThunk *identity(int unused);
};

Rva122980IdentityWithArgumentThunk *Rva122980IdentityWithArgumentThunk::identity(int)
{
    return this;
}
