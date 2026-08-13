struct Rva97920IdentityWithArgumentThunk
{
    Rva97920IdentityWithArgumentThunk *identity(int unused);
};

Rva97920IdentityWithArgumentThunk *Rva97920IdentityWithArgumentThunk::identity(int)
{
    return this;
}
