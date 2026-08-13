struct RvaCADC0IdentityWithArgumentThunk
{
    RvaCADC0IdentityWithArgumentThunk *identity(int unused);
};

RvaCADC0IdentityWithArgumentThunk *RvaCADC0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
