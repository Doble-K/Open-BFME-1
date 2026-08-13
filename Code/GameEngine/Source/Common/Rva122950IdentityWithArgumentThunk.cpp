struct Rva122950IdentityWithArgumentThunk
{
    Rva122950IdentityWithArgumentThunk *identity(int unused);
};

Rva122950IdentityWithArgumentThunk *Rva122950IdentityWithArgumentThunk::identity(int)
{
    return this;
}
