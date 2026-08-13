struct Rva14A960IdentityWithArgumentThunk
{
    Rva14A960IdentityWithArgumentThunk *identity(int unused);
};

Rva14A960IdentityWithArgumentThunk *Rva14A960IdentityWithArgumentThunk::identity(int)
{
    return this;
}
