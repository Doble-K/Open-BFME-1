struct RvaCB0D0IdentityWithArgumentThunk
{
    RvaCB0D0IdentityWithArgumentThunk *identity(int unused);
};

RvaCB0D0IdentityWithArgumentThunk *RvaCB0D0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
