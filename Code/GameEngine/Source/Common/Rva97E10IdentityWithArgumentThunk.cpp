struct Rva97E10IdentityWithArgumentThunk
{
    Rva97E10IdentityWithArgumentThunk *identity(int unused);
};

Rva97E10IdentityWithArgumentThunk *Rva97E10IdentityWithArgumentThunk::identity(int)
{
    return this;
}
