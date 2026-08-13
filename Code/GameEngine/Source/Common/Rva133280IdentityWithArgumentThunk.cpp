struct Rva133280IdentityWithArgumentThunk
{
    Rva133280IdentityWithArgumentThunk *identity(int unused);
};

Rva133280IdentityWithArgumentThunk *Rva133280IdentityWithArgumentThunk::identity(int)
{
    return this;
}
