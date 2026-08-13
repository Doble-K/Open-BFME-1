struct Rva92A00IdentityWithArgumentThunk
{
    Rva92A00IdentityWithArgumentThunk *identity(int unused);
};

Rva92A00IdentityWithArgumentThunk *Rva92A00IdentityWithArgumentThunk::identity(int)
{
    return this;
}
