struct Rva191F70IdentityWithArgumentThunk
{
    Rva191F70IdentityWithArgumentThunk *identity(int unused);
};

Rva191F70IdentityWithArgumentThunk *Rva191F70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
