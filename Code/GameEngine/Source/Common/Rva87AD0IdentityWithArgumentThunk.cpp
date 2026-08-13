struct Rva87AD0IdentityWithArgumentThunk
{
    Rva87AD0IdentityWithArgumentThunk *identity(int unused);
};

Rva87AD0IdentityWithArgumentThunk *Rva87AD0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
