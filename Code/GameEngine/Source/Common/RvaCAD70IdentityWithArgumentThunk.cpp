struct RvaCAD70IdentityWithArgumentThunk
{
    RvaCAD70IdentityWithArgumentThunk *identity(int unused);
};

RvaCAD70IdentityWithArgumentThunk *RvaCAD70IdentityWithArgumentThunk::identity(int)
{
    return this;
}
