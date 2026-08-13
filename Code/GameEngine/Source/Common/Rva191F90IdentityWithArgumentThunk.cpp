struct Rva191F90IdentityWithArgumentThunk
{
    Rva191F90IdentityWithArgumentThunk *identity(int unused);
};

Rva191F90IdentityWithArgumentThunk *Rva191F90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
