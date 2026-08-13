struct Rva122A90IdentityWithArgumentThunk
{
    Rva122A90IdentityWithArgumentThunk *identity(int unused);
};

Rva122A90IdentityWithArgumentThunk *Rva122A90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
