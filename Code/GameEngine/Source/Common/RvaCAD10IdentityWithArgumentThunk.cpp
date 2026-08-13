struct RvaCAD10IdentityWithArgumentThunk
{
    RvaCAD10IdentityWithArgumentThunk *identity(int unused);
};

RvaCAD10IdentityWithArgumentThunk *RvaCAD10IdentityWithArgumentThunk::identity(int)
{
    return this;
}
