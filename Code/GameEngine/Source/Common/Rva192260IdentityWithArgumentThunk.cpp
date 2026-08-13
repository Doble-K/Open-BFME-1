struct Rva192260IdentityWithArgumentThunk
{
    Rva192260IdentityWithArgumentThunk *identity(int unused);
};

Rva192260IdentityWithArgumentThunk *Rva192260IdentityWithArgumentThunk::identity(int)
{
    return this;
}
