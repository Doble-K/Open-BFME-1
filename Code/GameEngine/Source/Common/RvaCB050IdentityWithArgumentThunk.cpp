struct RvaCB050IdentityWithArgumentThunk
{
    RvaCB050IdentityWithArgumentThunk *identity(int unused);
};

RvaCB050IdentityWithArgumentThunk *RvaCB050IdentityWithArgumentThunk::identity(int)
{
    return this;
}
