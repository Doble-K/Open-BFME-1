struct Rva92A40IdentityWithArgumentThunk
{
    Rva92A40IdentityWithArgumentThunk *identity(int unused);
};

Rva92A40IdentityWithArgumentThunk *Rva92A40IdentityWithArgumentThunk::identity(int)
{
    return this;
}
