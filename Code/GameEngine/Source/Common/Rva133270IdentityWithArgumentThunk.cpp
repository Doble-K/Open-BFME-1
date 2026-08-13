struct Rva133270IdentityWithArgumentThunk
{
    Rva133270IdentityWithArgumentThunk *identity(int unused);
};

Rva133270IdentityWithArgumentThunk *Rva133270IdentityWithArgumentThunk::identity(int)
{
    return this;
}
