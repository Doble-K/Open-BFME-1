struct Rva94CC0IdentityWithArgumentThunk
{
    Rva94CC0IdentityWithArgumentThunk *identity(int unused);
};

Rva94CC0IdentityWithArgumentThunk *Rva94CC0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
