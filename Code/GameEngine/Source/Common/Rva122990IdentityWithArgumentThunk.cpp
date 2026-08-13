struct Rva122990IdentityWithArgumentThunk
{
    Rva122990IdentityWithArgumentThunk *identity(int unused);
};

Rva122990IdentityWithArgumentThunk *Rva122990IdentityWithArgumentThunk::identity(int)
{
    return this;
}
