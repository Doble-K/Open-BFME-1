struct Rva191FA0IdentityWithArgumentThunk
{
    Rva191FA0IdentityWithArgumentThunk *identity(int unused);
};

Rva191FA0IdentityWithArgumentThunk *Rva191FA0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
