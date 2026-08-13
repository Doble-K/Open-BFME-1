struct RvaCB120IdentityWithArgumentThunk
{
    RvaCB120IdentityWithArgumentThunk *identity(int unused);
};

RvaCB120IdentityWithArgumentThunk *RvaCB120IdentityWithArgumentThunk::identity(int)
{
    return this;
}
