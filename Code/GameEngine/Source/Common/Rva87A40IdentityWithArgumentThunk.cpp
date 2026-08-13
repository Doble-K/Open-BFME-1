struct Rva87A40IdentityWithArgumentThunk
{
    Rva87A40IdentityWithArgumentThunk *identity(int unused);
};

Rva87A40IdentityWithArgumentThunk *Rva87A40IdentityWithArgumentThunk::identity(int)
{
    return this;
}
