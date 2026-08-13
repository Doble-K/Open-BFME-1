struct RvaCAD90IdentityWithArgumentThunk
{
    RvaCAD90IdentityWithArgumentThunk *identity(int unused);
};

RvaCAD90IdentityWithArgumentThunk *RvaCAD90IdentityWithArgumentThunk::identity(int)
{
    return this;
}
