struct RvaCAD80IdentityWithArgumentThunk
{
    RvaCAD80IdentityWithArgumentThunk *identity(int unused);
};

RvaCAD80IdentityWithArgumentThunk *RvaCAD80IdentityWithArgumentThunk::identity(int)
{
    return this;
}
