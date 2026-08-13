struct PentadenaryIdentityWithArgumentThunk
{
    PentadenaryIdentityWithArgumentThunk *identity(int unused);
};

PentadenaryIdentityWithArgumentThunk *PentadenaryIdentityWithArgumentThunk::identity(int)
{
    return this;
}
