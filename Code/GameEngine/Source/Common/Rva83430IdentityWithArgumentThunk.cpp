struct Rva83430IdentityWithArgumentThunk
{
    Rva83430IdentityWithArgumentThunk *identity(int unused);
};

Rva83430IdentityWithArgumentThunk *Rva83430IdentityWithArgumentThunk::identity(int)
{
    return this;
}
