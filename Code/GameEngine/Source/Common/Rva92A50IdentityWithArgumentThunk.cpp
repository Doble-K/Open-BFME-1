struct Rva92A50IdentityWithArgumentThunk
{
    Rva92A50IdentityWithArgumentThunk *identity(int unused);
};

Rva92A50IdentityWithArgumentThunk *Rva92A50IdentityWithArgumentThunk::identity(int)
{
    return this;
}
