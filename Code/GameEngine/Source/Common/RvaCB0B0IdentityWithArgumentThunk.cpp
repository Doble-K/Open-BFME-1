struct RvaCB0B0IdentityWithArgumentThunk
{
    RvaCB0B0IdentityWithArgumentThunk *identity(int unused);
};

RvaCB0B0IdentityWithArgumentThunk *RvaCB0B0IdentityWithArgumentThunk::identity(int)
{
    return this;
}
