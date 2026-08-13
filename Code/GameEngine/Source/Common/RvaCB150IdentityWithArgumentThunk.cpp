struct RvaCB150IdentityWithArgumentThunk
{
    RvaCB150IdentityWithArgumentThunk *identity(int unused);
};

RvaCB150IdentityWithArgumentThunk *RvaCB150IdentityWithArgumentThunk::identity(int)
{
    return this;
}
